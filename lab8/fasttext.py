def csv_row(row):
    label = (int)(row['is_amendment'])
    text = row['text'].replace('\n', ' ').replace('\r', '').replace(
        "\"", "\"\"")
    return '__label__{0}, "{1}"\n'.format(label, text)


def prepare_files(df, path):
    with open(path, 'w', encoding='utf-8') as f:
        for _, row in df.iterrows():
            f.write(csv_row(row))
