import pandas as pd

from sklearn.svm import SVC
from sklearn.feature_extraction.text import TfidfVectorizer, CountVectorizer
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

    return clf.score(X, y)


def teach_svm(train, validation, df, stopwords):
    best_score = None
    best_classifier = None
    metrics = []

    for drop_threshold in [0, 100, 1000, 5000]:
        vocabulary = build_vocabulary(
            df, drop_threshold, drop_exceptions=['"ust.', '"art.'])
        for kernel in ['linear', 'poly', 'rbf', 'sigmoid']:
            for tol in [1e-11, 1e-09, 1e-07, 1e-05, 1e-02, 1]:
                for C in [0.1, 1, 5, 10, 100, 200]:
                    clf = SVC(tol=tol, C=C, kernel=kernel)
                    clf = teach_classifier(clf, train, vocabulary, stopwords)
                    score = evaluate(validation, clf, vocabulary, stopwords)

                    if best_score is None or score > best_score:
                        best_score = score
                        best_classifier = clf
                        print(
                            'Score {0} for tol={1}, c={2}, kernel={3}, drop={4}'
                            .format(score, tol, C, kernel, drop_threshold))

                    metrics.append((tol, C, score, kernel, drop_threshold))

    metric_df = pd.DataFrame(
        metrics, columns=['tol', 'C', 'score', 'kernel', 'drop_threshold'])

    return best_classifier, metric_df
