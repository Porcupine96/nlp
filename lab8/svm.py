import pandas as pd

from sklearn.svm import SVC
from sklearn.feature_extraction.text import TfidfVectorizer, CountVectorizer
from sklearn.metrics import precision_recall_fscore_support

from util import build_vocabulary


def teach_classifier(clf, train, vocabulary, stopwords):
    vectorizer = TfidfVectorizer(vocabulary=vocabulary, stop_words=stopwords)
    X = vectorizer.fit_transform(train['text'])
    y = train['is_amendment']

    clf.fit(X, y)
    return clf


def evaluate(test, clf, vocabulary, stopwords):
    vectorizer = TfidfVectorizer(vocabulary=vocabulary, stop_words=stopwords)
    X = vectorizer.fit_transform(test['text'])
    y = test['is_amendment']

    _, _, f1, _ = precision_recall_fscore_support(
        y, svm_predict(clf, test, vocabulary, stopwords), average='weighted')

    return f1


def teach_svm(train, validation, df, stopwords):
    best_score = None
    best_classifier = None
    best_metrics = None
    best_vocabulary = None
    metrics = []

    for drop_threshold in [0, 1000, 3000, 5000]:
        vocabulary = build_vocabulary(
            df, drop_threshold, drop_exceptions=['"ust.', '"art.'])
        for kernel in ['rbf']:
            for tol in [1e-11, 1e-05, 1e-02, 1]:
                for C in [0.1, 1, 100, 200]:
                    clf = SVC(tol=tol, C=C, kernel=kernel)
                    clf = teach_classifier(clf, train, vocabulary, stopwords)
                    score = evaluate(validation, clf, vocabulary, stopwords)
                    step_metrics = (tol, C, score, kernel, drop_threshold)

                    if best_score is None or score > best_score:
                        best_score = score
                        best_classifier = clf
                        best_metrics = step_metrics
                        best_vocabulary = vocabulary
                        print(
                            'Score {0} for tol={1}, c={2}, kernel={3}, drop={4}'
                            .format(score, tol, C, kernel, drop_threshold))

                    metrics.append(step_metrics)

    metric_df = pd.DataFrame(
        metrics, columns=['tol', 'C', 'score', 'kernel', 'drop_threshold'])

    return best_classifier, best_vocabulary, best_metrics, metric_df


def teach_progressive_svm(train, validation, test, stopwords, tol, C,
                          drop_threshold):
    df = pd.concat([train, validation, test])

    vocabulary = build_vocabulary(
        df, drop_threshold, drop_exceptions=['"ust.', '"art.'])

    results = {}

    for train_size in range(100, 1200, 100):
        train_split = train[:train_size]
        clf = SVC(tol=tol, C=C)
        clf = teach_classifier(clf, train_split, vocabulary, stopwords)
        validation_score = evaluate(validation, clf, vocabulary, stopwords)
        test_score = evaluate(test, clf, vocabulary, stopwords)
        results[train_size] = (train_size, validation_score, test_score)

    return results


def svm_predict(clf, test, vocabulary, stopwords):
    vectorizer = TfidfVectorizer(vocabulary=vocabulary, stop_words=stopwords)
    X = vectorizer.fit_transform(test['text'])
    return clf.predict(X)


def svm_show_scores(clf, test, vocabulary, stopwords):
    p, r, f1, _ = precision_recall_fscore_support(
        test['is_amendment'],
        svm_predict(clf, test, vocabulary, stopwords),
        average='weighted')

    print('Precision: {0}'.format(p))
    print('Recall:    {0}'.format(r))
    print('F1 score:  {0}'.format(f1))
