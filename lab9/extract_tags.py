import pandas as pd
import xml.etree.ElementTree as ET

from main import read_bills


class Entity:
    def __init__(self, orth, lex, ner, ner_nr):
        self.orth = orth
        self.lex = lex
        self.ner = ner
        self.ner_nr = ner_nr

        if ner is None:
            self.coarse_ner = None
        else:
            self.coarse_ner = '_'.join(ner.split('_')[:2])

    def __str__(self):
        return '{} {} {}'.format(self.orth, self.coarse_ner, self.ner)


def extract_entities(content):
    entities = []
    root = ET.fromstring(content)

    for chunk in root:
        for sentence in chunk:
            for tok in sentence:
                if tok.tag == 'tok':
                    orth = tok.find('orth').text
                    lex = tok.find('lex/base').text
                    ner, ner_nr = (None, None)

                    ann = tok.find('ann')
                    if ann is not None:
                        ner = ann.attrib['chan']
                        ner_nr = ann.text

                    entities.append(Entity(orth, lex, ner, ner_nr))

    return entities


def entities_dataframe(tagged_bills):
    results = []
    for name, content in tagged_bills.items():
        for entity in extract_entities(content):
            results.append((name, entity.orth, entity.lex, entity.ner,
                            entity.coarse_ner, entity.ner_nr))

    return pd.DataFrame(
        results,
        columns=['bill_path', 'orth', 'lex', 'ner', 'coarse_ner', 'ner_nr'])
