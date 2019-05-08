import numpy as np
import pandas as pd


def split_ttf(df, split=(60, 20, 20)):
    assert (len(split) == 3)
    assert (sum(split) == 100)

    shuffled = df.copy()
    np.random.shuffle(shuffled.values)

    train_count = (split[0] * len(df)) // 100
    test_count = (split[1] * len(df)) // 100

    test = shuffled[:train_count]
    train = shuffled[train_count:(train_count + test_count)]
    validation = shuffled[(train_count + test_count):]

    return test, train, validation
