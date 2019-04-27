type synsetId = int;

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
};