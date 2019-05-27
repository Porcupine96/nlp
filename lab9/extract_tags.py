import pandas as pd
import xml.etree.ElementTree as ET

from main import read_bills


class Entity:
    def __init__(self, orth, lex, ner):
        self.orth = orth
        self.lex = lex
        self.ner = ner

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
            last_ner_nr = 0
            last_ann = None
            orth_in_progress = None
            lex_in_progress = None
            for tok in sentence:
                if tok.tag == 'tok':
                    orth = tok.find('orth').text
                    lex = tok.find('lex/base').text
                    ner = None

                    ann = tok.find('ann')
                    if ann is not None:
                        ner = ann.attrib['chan']
                        ner_nr = ann.text

                        # no chain
                        if last_ann is None and str(ner_nr) == '0':
                            pass

                        # no chain - start a new chain
                        elif last_ann is None:
                            orth_in_progress = orth
                            lex_in_progress = lex
                            last_ann = ann
                        # in the middle of a chain - finish the chain
                        elif str(ner_nr) == '0' or last_ann.attrib[
                                'chan'] != ann.attrib['chan']:
                            entities.append(
                                Entity(orth_in_progress, lex_in_progress,
                                       last_ann.attrib['chan']))
                            orth_in_progress = None
                            lex_in_progress = None
                            last_ann = None
                        # in the middle of a chain - continue
                        else:
                            orth_in_progress += ' {}'.format(orth)
                            lex_in_progress += ' {}'.format(lex)
                            last_ann = ann
                    # no chain - current token without ann
                    elif last_ann is None:
                        pass
                    # in the middle of a chain - current token without ann
                    else:
                        entities.append(
                            Entity(orth_in_progress, lex_in_progress,
                                   last_ner))
                        orth_in_progress = None
                        lex_in_progress = None
                        last_ann = None
    return entities


def entities_dataframe(tagged_bills):
    results = []
    for name, content in tagged_bills.items():
        for entity in extract_entities(content):
            results.append((name, entity.orth, entity.lex, entity.ner,
                            entity.coarse_ner))

    return pd.DataFrame(
        results, columns=['bill_path', 'orth', 'lex', 'ner', 'coarse_ner'])
