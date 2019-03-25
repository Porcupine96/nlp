#!/bin/bin/python

import os

from elasticsearch import Elasticsearch
from elasticsearch.helpers import bulk

es = Elasticsearch(['localhost:9200'])

query = {
    "query": {
        "match": {
            "doc.content": {
                "query": "ustawa"
            }
        }
    },
    "_source": False,
    "explain": True,
    "size": 1200
}

results = es.search(index="bill_index", body=query)

total_value = 0
for res in results['hits']['hits']:
    for details_exp in res['_explanation']['details']:
        for details_group in details_exp['details']:
            for details in details_group['details']:
                if details['description'].startswith('termFreq'):
                    total_value += int(details['value'])

print('Total: {0}'.format(total_value))
