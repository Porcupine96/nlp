open Belt;

type sense = {
  id: int,
  lemma: string,
  partOfSpeech: string,
  senseNumber: int,
};

type synset = {
  synsetId: int,
  senses: list(sense),
};

type relationKind =
  | Hyponym
  | Hypernymy
  | Other;

type relation = {
  id: int,
  relFrom: int,
  relTo: int,
  relationKind,
  relationId: int,
  relationName: string,
};

module RelationCmp =
  Belt.Id.MakeComparable({
    type t = relation;
    let cmp = (a, b) => a.id - b.id;
  });

let distinctSynsets = (relations: list(relation)) =>
  relations->List.map(relation => [relation.relFrom, relation.relTo])->List.flatten->List.toArray->Belt_SetInt.fromArray->Belt_SetInt.toList;