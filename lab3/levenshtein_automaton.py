#!/bin/bash

from itertools import groupby

ANY = 'ANY'
EPSILON = 'EPS'
START = (0, 0)

ALPHABET = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'


class Automaton():
    def __init__(self):
        self.transitions = {START: []}

    def add_final(self, state):
        self.final = state
        self.transitions[state] = []

    def add_transition(self, node_from, node_to, transition):
        if self.transitions.get(node_from) is None:
            self.transitions[node_from] = [(node_to, transition)]
        else:
            self.transitions[node_from] += [(node_to, transition)]

    def __repr__(self):
        repr = ''
        for node, transitions in self.transitions.items():
            repr += '{0}: {1}\n'.format(node, transitions)
        return repr


def generate_automaton(term, k):
    automaton = Automaton()

    for i, c in enumerate(term):
        for e in range(k + 1):
            if e < k and i < len(term):
                automaton.add_transition((i, e), (i + 1, e + 1), EPSILON)
                automaton.add_transition((i, e), (i + 1, e + 1), ANY)
            if e < k:
                automaton.add_transition((i, e), (i, e + 1), ANY)
            if i < len(term):
                automaton.add_transition((i, e), (i + 1, e), c)

    term_len = len(term)
    for e in range(k + 1):
        if e < k:
            automaton.add_transition((term_len, e), (term_len, e + 1), ANY)

    automaton.add_final((term_len, k))

    return automaton


def generate_terms(term, automaton):
    terms = {n: set() for n, _ in automaton.transitions.items()}
    terms[START].add('')

    queue = [START]
    while len(queue) > 0:
        current_node, *rest = queue
        queue = rest

        for next_node, transition in automaton.transitions[current_node]:
            for term in update_terms(terms[current_node], transition):
                if term not in terms[next_node]:
                    terms[next_node].add(term)

            queue.append(next_node)

    return terms[automaton.final]


def update_terms(terms, transition):
    new_terms = []

    if transition == 'ANY':
        new_terms = [term + letter for term in terms for letter in ALPHABET]
    elif transition == 'EPS':
        new_terms = terms
    else:
        new_terms = [term + transition for term in terms]

    return new_terms


def debug_print(terms):
    by_len = lambda x: len(x)
    for length, words in groupby(sorted(terms, key=by_len), key=by_len):
        print('{} - {}'.format(length, list(words)))


def levenshtein(word, k):
    automaton = generate_automaton(word, k)
    terms = generate_terms(word, automaton)
    return terms
