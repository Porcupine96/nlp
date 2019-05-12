import pandas as pd

from regex import regex


def preprocess_bill(bill_path, bill_content):
    try:
        header_pattern = r'[Uu]\s*[Ss]\s*[Tt]\s*[Aa]\s*[Ww]\s*[Aa][\s\d\p{L}\p{P}]+?(?=Rozdział|Art)'
        header_scanner = list(regex.finditer(header_pattern, bill_content))[0]
        header_end = header_scanner.end()
        header = bill_content[:header_end]
        body = bill_content[header_end:].replace(u'\xa0', u' ')
        amendment_pattern = 'o zmianie ustawy|o zmianie niektórych ustaw'
        is_amendment = len(regex.findall(amendment_pattern, header)) > 0

        return (bill_path, body, is_amendment)
    except:
        print('Could not resolve header for ' + bill_path)
        return None


def preprocess_all(bills):
    results = []
    for bill_path, bill_content in bills.items():
        results.append(preprocess_bill(bill_path, bill_content))
    # TODO: fix remaining
    return pd.DataFrame(
        results[:949] + results[951:],
        columns=['bill_file', 'text', 'is_amendment'])


def custom_tokenize(text):
    tokens = []
    words = text.split()

    for word in words:
        w = word.lower()
        if w.isalpha() \
           or w.startswith('art') or w.startswith('"art') \
           or w.startswith('ust') or w.startswith('"ust'):
            tokens.append(w)
    return tokens


def extract_tokens(text):
    normalized_tokens = []
    tokens = custom_tokenize(text)
    tokens_length = len(tokens)

    for i in range(tokens_length):
        normalized = tokens[i]

        if len(normalized) > 0:
            if 0 < i < tokens_length - 1 \
               and tokens[i - 1] == '``' \
               and tokens[i + 1] == "''" \
               and tokens[i].starswith('art'):
                normalized_tokens.append('"' + normalized + '""')
            else:
                normalized_tokens.append(normalized)

    return normalized_tokens
