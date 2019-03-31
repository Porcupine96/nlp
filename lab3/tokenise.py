#!/usr/bin/env python3

import os
import pickle

from nltk.tokenize import word_tokenize
from collections import Counter


def read_bills(data_path):
    bills = {}
    for file_name in os.listdir(data_path):
        path = os.path.join(data_path, file_name)
        with open(path, 'r') as f:
            content = f.readlines()
            bills[file_name] = '\n'.join(content)
    return bills


def is_valid(term):
    return term.isalpha() and len(term) >= 2


def bill_tokens(bill_content):
    tokens = [
        token.lower() for token in word_tokenize(bill_content)
        if is_valid(token)
    ]

    return Counter(tokens)


data_path = '../lab2/data'

frequency_dict = Counter()

for _, bill_content in read_bills(data_path).items():
    frequency_dict.update(bill_tokens(bill_content))

pickle.dump(dict(frequency_dict), open('frequency_dict.p', 'wb'))
