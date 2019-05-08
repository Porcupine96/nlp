import pandas as pd


def variant_i(df):
    return df.copy()


def variant_ii(df):
    df_copy = df.copy()
    df_copy['text'] = df_copy.apply(lambda r: take_percent(r['text'], pct=10))

    return df_copy


def variant_iii(df):
    df_copy = df.copy()
    df_copy['text'] = df_copy.apply(lambda r: take_lines(r['text'], lines=10))

    return df_copy


def variant_iv(df):
    df_copy = df.copy()
    df_copy['text'] = df_copy.apply(lambda r: take_lines(r['text'], lines=1))

    return df_copy


def take_percent(text, pct):
    pass


def take_lines(text, lines):
    pass
