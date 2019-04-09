import os
from collections import Counter

import numpy as np
import regex
from nltk.tokenize import word_tokenize

from llr import llr_2x2


def read_stopwords(path):
    with open(path, 'r') as f:
        return [regex.sub(r'\s', '', word) for word in f.readlines()]


def read_bills(data_path):
    bills = {}
    for file_name in os.listdir(data_path):
        path = os.path.join(data_path, file_name)
        with open(path, 'r') as f:
            lines = f.readlines()
            bills[file_name] = '\n'.join(lines)
    return bills


def normalize(tokens):
    normalized_tokens = []

    for token in tokens:
        normalized = token.lower()
        if len(normalized) > 0 and token.isalpha() and token:
            normalized_tokens.append(normalized)

    return normalized_tokens


def calculate_counters(bill_content, stop_words):
    tokens = normalize(word_tokenize(bill_content))

    bigram_counter = Counter()
    left_word_counter = Counter(tokens)
    right_word_counter = Counter(tokens)

    for i in range(len(tokens) - 1):
        if tokens[i] not in stop_words and tokens[i + 1] not in stop_words:
            bigram = (tokens[i], tokens[i + 1])
            bigram_counter[bigram] += 1
            left_word_counter[tokens[i]] += 1
            right_word_counter[tokens[i + 1]] += 1

    return left_word_counter, right_word_counter, bigram_counter


def global_counters(bills, stop_words):
    bigram_counter = Counter()
    left_word_counter = Counter()
    right_word_counter = Counter()
    for _, content in list(bills.items()):
        left, right, bigram = calculate_counters(content, stop_words)
        bigram_counter.update(bigram)
        left_word_counter.update(left)
        right_word_counter.update(right)
    return left_word_counter, right_word_counter, bigram_counter


def calculate_pmi(left_word_counter, right_word_counter, bigram_counter, count_threshold=7):
    bigram_count = sum([count for _, count in dict(bigram_counter).items()])

    pmi_results = {}
    for (a, b), count in dict(bigram_counter).items():
        if left_word_counter[a] >= count_threshold and right_word_counter[b] >= count_threshold:
            pmi = (count * bigram_count) / (left_word_counter[a] * right_word_counter[b])
            pmi_results[(a, b)] = np.log(pmi)
    return pmi_results


def calculate_llr(left_word_counter, right_word_counter, bigram_counter):
    left_word_counter_dict = dict(left_word_counter)
    right_word_counter_dict = dict(right_word_counter)
    bigram_counter_dict = dict(bigram_counter)
    total_bigrams = sum([count for _, count in bigram_counter_dict.items()])

    llr_results = {}
    for bigram, _ in bigram_counter_dict.items():
        table = contingency_table(bigram, left_word_counter_dict,
                                  right_word_counter_dict, bigram_counter_dict, total_bigrams)
        llr_results[bigram] = llr_2x2(*table)
    return llr_results


def contingency_table(bigram, left_word_counter, right_word_counter, bigram_counter, total):
    a, b = bigram

    k11 = bigram_counter[bigram]
    k12 = left_word_counter[a] - k11
    k21 = right_word_counter[b] - k11
    k22 = total - (k11 + k12 + k21)

    return k11, k12, k21, k22


def highest_scores(result_dictionary, n):
    return sorted(result_dictionary.items(), key=lambda x: x[1], reverse=True)[:n]


def pretty_print(bigram_scores):
    for bigram, score in bigram_scores:
        bigram_str = bigram[0] + ' ' + bigram[1]
        print('{0:40}: {1}'.format(bigram_str, score))


def sample(result_dictionary, step=100):
    sorted_results = sorted(result_dictionary.items(), key=lambda x: x[1], reverse=True)

    for i in range(len(sorted_results)):
        if i + 2 < len(sorted_results) and i % step == 0:
            print(sorted_results[i])
            print(sorted_results[i + 1])
            print(sorted_results[i + 2])
            print('-------------------')


print('Started...')

bill_data_path = '../lab2/data'
all_bills = read_bills(bill_data_path)
polish_stopwords = read_stopwords('./data/stopwords-pl.txt')

print('Data loaded...')

global_left_counter, global_right_counter, global_bigram_counter = global_counters(all_bills, polish_stopwords)

print('Counters calculated...')

pretty_print(highest_scores(calculate_pmi(global_left_counter, global_right_counter, global_bigram_counter), 30))
# pretty_print(highest_scores(calculate_llr(global_left_counter, global_right_counter, global_bigram_counter), 30))

# sample(calculate_pmi(global_word_counter, global_bigram_counter))
# sample(calculate_llr(global_word_counter, global_bigram_counter))

print('Finished...')
