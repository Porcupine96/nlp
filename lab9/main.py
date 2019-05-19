import os
import io
import requests
import random

result_dir = 'results'
url = 'http://ws.clarin-pl.eu/nlprest2/base/process'


def read_bills(data_path):
    bills = {}
    for file_name in os.listdir(data_path):
        path = os.path.join(data_path, file_name)
        with io.open(path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            bills[file_name] = '\n'.join(lines)
    return bills


def random_bills(bills, n):
    bill_items = bills.items()
    random.shuffle(bill_items)
    return bill_items[:n]


def make_request(text):
    data = {
        'lpmn': 'any2txt|wcrft2|liner2({"model":"n82"})',
        'text': text,
        'user': 'moj@adres.email'
    }

    response = requests.post(url, json=data, timeout=1200)
    response.encoding = 'utf-8'
    return response.text


def __main__():
    bills = random_bills(read_bills('../lab1/data'), n=25)

    for name, content in bills:
        print('processing: {}'.format(name))
        try:
            response = make_request(content)
            with io.open(
                    os.path.join(result_dir, name), 'w',
                    encoding='utf-8') as f:
                f.writelines(response)
        except:
            print('failed to process: {}'.format(name))
