#!/usr/bin/env python3

import time as t
import numpy as np
import matplotlib.pyplot as plt

from string import ascii_lowercase
from levenshtein_automaton import levenshtein


def measure(operation, retries=10):
    results = []
    for _ in range(retries):
        start = t.time()
        operation()
        end = t.time()
        results.append(end - start)

    return np.average(results), np.std(results)


max_size = 20

sizes = range(1, max_size + 1)
times = []
times_std = []

for size in sizes:
    time, time_std = measure(lambda: levenshtein(ascii_lowercase[:size], k=1))
    times.append(time)
    times_std.append(time_std)

plt.errorbar(sizes, times, yerr=times_std, fmt='.')
plt.xlabel('size')
plt.ylabel('time [s]')
plt.show()
