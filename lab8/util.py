import os
import numpy as np
import regex
import pandas as pd

from preprocess import extract_tokens
from collections import Counter


def read_bills(data_path):
    bills = {}
    for file_name in os.listdir(data_path):
        path = os.path.join(data_path, file_name)
        with open(path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            bills[file_name] = '\n'.join(lines)
    return bills


def read_stopwords(path):
    with open(path, 'r') as f:
        return [regex.sub(r'\s', '', word) for word in f.readlines()]


def split_ttf(df, split=(60, 20, 20)):
    assert (len(split) == 3)
    assert (sum(split) == 100)

    shuffled = df.copy()
    np.random.shuffle(shuffled.values)

    train_count = (split[0] * len(df)) // 100
    test_count = (split[1] * len(df)) // 100

    test = shuffled[:train_count]
    train = shuffled[train_count:(train_count + test_count + 1)]
    validation = shuffled[(train_count + test_count + 1):]

    return test, train, validation


def build_vocabulary(df, drop_threshold, drop_exceptions):
    token_counter = Counter()
    for text in df['text']:
        token_counter.update(Counter(extract_tokens(text)))

    vocabulary = []
    for token, count in token_counter.items():
        if count > drop_threshold or token in drop_exceptions:
            vocabulary.append(token)
    return vocabulary


def f1_score(precision, recall):
    return 2 * (precision * recall) / (precision + recall)
