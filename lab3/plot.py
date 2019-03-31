#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

from util import load_frequencies

frequency_dict = load_frequencies('frequency_dict.p')

sorted_by_name = sorted(frequency_dict.items(), key=lambda x: x[0])
sorted_by_freq = sorted(sorted_by_name, key=lambda x: x[1], reverse=True)

top = sorted_by_freq[:100]

terms, freqs = zip(*top)
indices = range(len(top))

plt.bar(indices, freqs)
plt.yscale('log')
plt.xticks(indices, terms, rotation='vertical')

plt.show()
