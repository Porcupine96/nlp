# Elasticsearch Assignment

Created: Mar 24, 2019 8:13 PM
NoteType: Assignment
Subject: NLP

### Install ElasticSearch (ES) + Install an ES plugin for Polish

Custom docker image:

- elasticsearch (version 6.4.2)
- morfologik plugin installed

**Dockerfile**

    FROM docker.elastic.co/elasticsearch/elasticsearch:6.4.2
    
    RUN ./bin/elasticsearch-plugin install pl.allegro.tech.elasticsearch.plugin:elasticsearch-analysis-morfologik:6.4.2

Kibana & Elasticsearch setup:

**docker-compose.yml**

    version: "3.2"
    services:
      elasticsearch:
        image: elastic-morfologik:0.1
        container_name: elasticsearch
        environment:
          - cluster.name=docker-cluster
          - bootstrap.memory_lock=true
          - discovery.type=single-node
          - discovery.zen.minimum_master_nodes=1
          - "ES_JAVA_OPTS=-Xms512m -Xmx512m"
        ulimits:
          memlock:
            soft: -1
            hard: -1
        volumes:
          - type: bind
            source: "./elk/elastic"
            target: /usr/share/elasticsearch/data
        ports:
          - "9200:9200"
      kibana:
        image: docker.elastic.co/kibana/kibana:6.4.2
        environment:
          - SERVER_NAME="Kibana"
          - SERVER_NAME=http://elasticsearch:9200
        volumes:
          - type: bind
            source: "./elk/kibana"
            target: /usr/share/kibana/data
        ports:
          - "5601:5601"

### Define an ES analyzer for Polish

**It should contain:**

- **standard tokenizer**
- **synonym filter with the following definitions:**
    1. **kpk - kodeks postępowania karnego**
    2. **kpc - kodeks postępowania cywilnego**
    3. **kk - kodeks karny**
    4. **kc - kodeks cywilny**
- **Morfologik-based lemmatizer**
- **lowercase filter**

Definition of the anlyzer with all the filters.

**analyser.json**

    {
      "settings": {
        "analysis": {
          "analyzer": {
            "bill_analyzer": {
              "type": "custom",
              "tokenizer": "standard",
              "filter": [
                "synonym",
                "morfologik_stem",
                "lowercase"
              ]
            }
          },
           "filter" : {
              "synonym" : {
                "type" : "synonym",
                "synonyms" : [
                  "kpk => kodeks postępowania karnego",
                  "kpc => kodeks postępowania cywilnego",
                  "kk => kodeks karny",
                  "kc => kodeks cywilny"
                ]
              }
          }
        }
      },
      "mappings": {
        "_doc": {
          "properties": {
            "doc.content": {
              "type": "text",
              "analyzer": "bill_analyzer",
              "search_analyzer": "bill_analyzer",
              "search_quote_analyzer": "bill_analyzer"
            }
          }
        }
      }
    }

### Define an ES index for storing the contents of the legislative acts

![](-80a7852a-d343-4047-b11c-3c39cbc413ceuntitled)

### Load the data to the ES index

Inserting the data using a python script:

**insert.py**

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

After loading the data we can view it in Kibana:

![](-f3391f31-bcf8-4ac2-a10f-b6e4b279357duntitled)

### Determine the number of legislative acts containing the word **ustawa** (in any form).

    {
      "query": {
        "match": {
          "doc.content": {
            "query": "ustawa"
          }
        }
      }
    }

Result: **1179**

The only document that did not match:

    POST /bill_index/_search?size=1
    {
      "query": {
        "bool": {
          "must_not": [
            {
              "term": { "doc.content": "ustawa" }
            }
          ]
        }
      }
    }

    "hits": {
        "total": 1,
        "max_score": 1,
        "hits": [
          {
            "_index": "bill_index",
            "_type": "document",
            "_id": "VAMDp2kBr3abYBHD9Ipq",
            "_score": 1,
            "_source": {
              "doc": {
                "file_name": "1996_400.txt",
                "content": [
                  "\n",
                  "\n",
                  "\n",
                  "\n",
                  "\n",
                  "Brak tekstu w postaci elektronicznej \n"
                ]
              }
            }
          }
        ]
      }

### Determine the number of legislative acts containing the words "**kodeks postępowania cywilnego"** in the specified order, but in an any inflection form

    {
      "query": {
        "match_phrase": {
          "doc.content": {
            "query": "kodeks postępowania cywilnego",
            "slop": 0
          }
        }
      }
    }

Result: **83**

### Determine the number of legislative acts containing the words **wchodzi w życie** (in any form) allowing for up to 2 additional words in the searched phrase

    {
      "query": {
        "match_phrase": {
          "doc.content": {
            "query": "wchodzi w życie",
            "slop": 2
          }
        }
      }
    }

Result: **1100**

### Determine the 10 documents that are the most relevant for the phrase **konstytucja**

    {
      "query": {
        "match": {
          "doc.content": {
            "query": "konstytucja"
          }
        }
      },
      "_source": ["doc.file_name"],
      "size": 10
    }

Result:

![](-b4dea552-b715-4ab4-a71d-70f41c544634untitled)

Results returned after a direct API call have slightly different (lower) scores than the ones returned in Kibana visualization:

    "hits": [
      {
        "_index": "bill_index",
        "_type": "_doc",
        "_id": "4gMbtWkBr3abYBHDQZ0S",
        "_score": 7.8775477,
        "_source": {
          "doc": {
            "file_name": "1997_629.txt"
          }
        }
      },
      {
        "_index": "bill_index",
        "_type": "_doc",
        "_id": "nAMbtWkBr3abYBHDQZ0Q",
        "_score": 7.5594935,
        "_source": {
          "doc": {
            "file_name": "1997_604.txt"
          }
        }
      },
      {
        "_index": "bill_index",
        "_type": "_doc",
        "_id": "BQMatWkBr3abYBHD-ppu",
        "_score": 6.9610863,
        "_source": {
          "doc": {
            "file_name": "1996_350.txt"
          }
        }
      },
      ... (remaining 7 bills)
    ]
    

### Print the excerpts containing the word **konstytucja** (up to three excerpts per document) from the previous task

    {
      "query": {
        "match": {
          "doc.content": {
            "query": "konstytucja"
          }
        }
      },
       "highlight" : {
            "fields" : {
                "doc.content" : {
                  "number_of_fragments": 3
                }
            }
      },
      "_source": "", 
      "size": 10
    }

Result:

    "hits": [
          {
            "_index": "bill_index",
            "_type": "_doc",
            "_id": "4gMbtWkBr3abYBHDQZ0S",
            "_score": 7.8775477,
            "_source": {},
            "highlight": {
              "doc.content": [
                "i uchwalenia <em>Konstytucji</em> Rzeczypospolitej Polskiej",
                "Do zgłoszenia projektu <em>Konstytucji</em> załącza się wykaz",
                "Zasady, na których opierać się ma <em>Konstytucja</em> mogą"
              ]
            }
          },
          {
            "_index": "bill_index",
            "_type": "_doc",
            "_id": "nAMbtWkBr3abYBHDQZ0Q",
            "_score": 7.5594935,
            "_source": {},
            "highlight": {
              "doc.content": [
                "zgodności celów partii politycznej z <em>Konstytucją</em>.",
                "<em>Konstytucją</em>.",
                "Wnioski o stwierdzenie zgodności z <em>Konstytucją</em> celów"
              ]
            }
          },
          {
            "_index": "bill_index",
            "_type": "_doc",
            "_id": "BQMatWkBr3abYBHD-ppu",
            "_score": 6.9610863,
            "_source": {},
            "highlight": {
              "doc.content": [
                "Za naruszenie <em>Konstytucji</em> lub ustawy, w związku z zajmowanym",
                "<em>Konstytucję</em> lub ustawę.\";",
                "podstawie art. 111 <em>Konstytucji</em>."
              ]
            }
          },
          ... (remaining 7 bills)
    ]

### Additional: Total count of "ustawa"

**bill_count.py**

    #!/bin/bin/python
    
    import os
    
    from elasticsearch import Elasticsearch
    
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

Result**: 25092**