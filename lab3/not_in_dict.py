#!/usr/bin/env python3

import pickle

from util import load_frequencies, load_dict
from levenshtein_automaton import levenshtein

frequency_dict = load_frequencies('frequency_dict.p')
polish_dict = load_dict('polimorfologik/polimorfologik-2.1.txt')


def not_matching(frequency_dict, polish_dict):
    not_found = list(
        filter(lambda tf: tf[0] not in polish_dict, frequency_dict.items()))

    sorted_by_name = sorted(not_found, key=lambda x: x[0])
    sorted_by_freq = sorted(sorted_by_name, key=lambda x: x[1], reverse=True)
    return sorted_by_freq


def valid_corrections(word, frequency_dict, polish_dict, k):
    return [(word, frequency_dict[word]) for word in levenshtein(word, k)
            if word in polish_dict and word in frequency_dict]


def corrections(word, frequency_dict, polish_dict):
    v_corrections = valid_corrections(word, frequency_dict, polish_dict, k=1)

    if len(v_corrections) == 0 and len(word) <= 7:
        v_corrections = valid_corrections(
            word, frequency_dict, polish_dict, k=2)

    return sorted(v_corrections, key=lambda c: c[1], reverse=True)


results = not_matching(frequency_dict, polish_dict)
three_occurrences = [(term, freq) for term, freq in results if freq == 3]

# for term, freq in three_occurrences[:30]:
#     print('{0:25}: {1}'.format(term, freq))

for term, _ in three_occurrences[:30]:
    best_corrections = corrections(term, frequency_dict, polish_dict)[:3]
    best_corrections_str = ', '.join([c for c, _ in best_corrections])
    print('{0:25}: {1}'.format(term, best_corrections_str))
