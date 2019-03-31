#!/usr/bin/env python3

import pickle


def load_frequencies(pickle_path):
    with open(pickle_path, 'rb') as f:
        return pickle.load(f)


def load_dict(dict_path):
    words = set()
    with open(dict_path, mode='r', encoding='utf8') as f:
        for line in f.readlines():
            w1, w2, _ = line.split(';')
            words.add(w1)
            words.add(w2)
    return words
