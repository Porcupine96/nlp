import pandas as pd

from random import shuffle
from math import ceil


def variant_i(df):
    return df.copy()


def variant_ii(df):
    df_copy = df.copy()
    df_copy['text'] = df_copy['text'].apply(
        lambda text: take_percent(text, pct=10))

    return df_copy


def variant_iii(df):
    df_copy = df.copy()
    df_copy['text'] = df_copy['text'].apply(
        lambda text: take_lines(text, count=10))

    return df_copy


def variant_iv(df):
    df_copy = df.copy()
    df_copy['text'] = df_copy['text'].apply(
        lambda text: take_lines(text, count=1))

    return df_copy


def take_percent(text, pct):
    lines = get_lines(text)
    shuffle(lines)
    line_pct = ceil(pct * len(lines) / 100)
    return '\n'.join(lines[:line_pct])


def take_lines(text, count):
    lines = get_lines(text)
    shuffle(lines)
    return '\n'.join(lines[:count])


def get_lines(text):
    return [line.strip() for line in text.split('\n') if len(line.strip()) > 3]
