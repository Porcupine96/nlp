#!/usr/bin/python

import os

from elasticsearch import Elasticsearch
from elasticsearch.helpers import bulk


def read_bills(data_path):
    bills = {}
    for file_name in os.listdir(data_path):
        path = os.path.join(data_path, file_name)
        with open(path, 'r') as f:
            content = f.readlines()
            bills[file_name] = content
    return bills


def generate_documents(bills):
    for file_name, bill_content in bills.items():
        yield {
            "_index": "bill_index",
            "_type": "_doc",
            "doc": {
                "file_name": file_name,
                "content": bill_content
            }
        }


data_path = "./data"
bills = read_bills(data_path)

print('{0} files loaded'.format(len(bills)))

es = Elasticsearch(['localhost:9200'], retry_on_timeout=True)
bulk(es, generate_documents(bills))

print('finished')
