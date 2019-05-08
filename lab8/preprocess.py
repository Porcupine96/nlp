import os
import pandas as pd

from regex import regex


def read_bills(data_path):
    bills = {}
    for file_name in os.listdir(data_path):
        path = os.path.join(data_path, file_name)
        with open(path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            bills[file_name] = '\n'.join(lines)
    return bills


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
