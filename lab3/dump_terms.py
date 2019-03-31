#!/usr/bin/env python3

import pickle
from elasticsearch import Elasticsearch

index = 'bill_index'
es = Elasticsearch(timeout=60, retry_on_timeout=True)

all_documents_query = {
    "query": {
        "match_all": {}
    },
    "_source": False,
    "size": 1200
}

term_vector_query = {
    "offsets": False,
    "payloads": False,
    "positions": False,
    "term_statistics": False,
    "field_statistics": False
}

result = es.search(index=index, body=all_documents_query)


def is_valid(term):
    return term.isalpha() and len(term) >= 2


def build_frequency_dict():
    frequency_dict = {}

    for doc in result['hits']['hits']:
        document_id = doc['_id']

        vectors = es.termvectors(index, '_doc', document_id, term_vector_query)

        terms = vectors['term_vectors']['doc.content']['terms']

        for term, freq_obj in terms.items():
            if is_valid(term):
                freq = int(freq_obj['term_freq'])
                current_freq = frequency_dict.get(term, 0)
                frequency_dict[term] = current_freq + freq

    return frequency_dict


frequency_dict = build_frequency_dict()

pickle.dump(frequency_dict, open('frequency_dict.p', 'wb'))
