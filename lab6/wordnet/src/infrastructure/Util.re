open Belt;

let label = (synsetId: int, synsetMap: Belt_MapInt.t(Domain.synset)): string =>
  switch (synsetMap->Belt_MapInt.get(synsetId)) {
  | Some(synset) => synset.senses->List.reduce("", (acc, sense) => acc == "" ? sense.lemma : acc ++ "\n" ++ sense.lemma)
  | None => string_of_int(synsetId)
  };