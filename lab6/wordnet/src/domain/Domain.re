type synsetId = int;

type sense = {
  id: int,
  lemma: string,
  partOfSpeech: string,
};

type synset = {
  synsetId: int,
  senses: list(sense),
};

type relationKind =
  | Hypernymy
  | Other;

type relation = {
  id: int,
  relFrom: int,
  relTo: int,
  relationKind,
};