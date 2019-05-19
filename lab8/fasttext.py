import fastText
import pandas as pd

from util import f1_score
from sklearn.metrics import precision_recall_fscore_support


def prepare_text(text):
    return text.replace('\n', ' ').replace('\r', '').replace("\"", "\"\"")


def csv_row(row):
    label = (int)(row['is_amendment'])
    text = prepare_text(row['text'])
    return '__label__{0}, "{1}"\n'.format(label, text)


def prepare_files(df, path):
    with open(path, 'w', encoding='utf-8') as f:
        for _, row in df.iterrows():
            f.write(csv_row(row))


def evaluate(model, test):
    _, _, f1, _ = precision_recall_fscore_support(
        test['is_amendment'],
        fasttext_predict(model, test),
        average='weighted')
    return f1


def teach_fasttext(train_path, validation):
    best_score = None
    best_classifier = None
    metrics = []

    for lr in [i / 10 for i in range(1, 50, 5)]:
        for wordNgrams in [1, 2, 3]:
            model = fastText.train_supervised(
                train_path, lr=lr, wordNgrams=wordNgrams)

            score = evaluate(model, validation)

            if best_score is None or score > best_score:
                best_score = score
                best_classifier = model
                print('Score {0} for lr={1}, wordNgrams={2}'.format(
                    score, lr, wordNgrams))

            metrics.append((lr, score, wordNgrams))

    metric_df = pd.DataFrame(metrics, columns=['lr', 'score', 'wordNgrams'])

    return best_classifier, metrics


def extract_label(result):
    return (int)(result[0].replace('__label__', '').replace(',', ''))


def fasttext_predict(model, test):
    labels, _ = model.predict([prepare_text(text) for text in test['text']])
    return list(map(extract_label, labels))


def fasttext_show_scores(clf, test):
    p, r, f1, _ = precision_recall_fscore_support(
        test['is_amendment'], fasttext_predict(clf, test), average='weighted')

    print('Precision: {0}'.format(p))
    print('Recall:    {0}'.format(r))
    print('F1 score:  {0}'.format(f1))
