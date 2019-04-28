open Belt;
open Repromise.Rejectable;

let network = (synsetId: int, ~maxDepth: option(int)=Some(1), ()): Wordnet.jsRepromise(list(Domain.relation)) => {
  let visited = ref(Belt_SetInt.empty);
  let relationIds = ref(Belt_SetInt.empty);

  let rec _network = (synsetId: int, ~maxDepth: option(int)=Some(1), ()) =>
    switch (maxDepth) {
    | Some(0) => resolved([])
    | _ =>
      Wordnet.relationsForSynset(synsetId)
      |> andThen((relations: list(Domain.relation)) => {
           let newRelations = relations->List.keep(relation => !(relationIds^)->Belt_SetInt.has(relation.id));
           newRelations->List.forEach(relation => relationIds := (relationIds^)->Belt_SetInt.add(relation.id));

           Repromise.Rejectable.all(
             newRelations->List.map(relation =>
               switch (relation.relFrom, relation.relTo) {
               | (relFrom, relTo) when relFrom == synsetId && !(visited^)->Belt_SetInt.has(relTo) =>
                 visited := (visited^)->Belt_SetInt.add(relTo);
                 _network(relTo, ~maxDepth=maxDepth->Option.map(d => d - 1), ()) |> map(result => List.concat(newRelations, result));
               | (relFrom, relTo) when relTo == synsetId && !(visited^)->Belt_SetInt.has(relFrom) =>
                 visited := (visited^)->Belt_SetInt.add(relFrom);
                 _network(relFrom, ~maxDepth=maxDepth->Option.map(d => d - 1), ()) |> map(result => List.concat(newRelations, result));
               | _ => resolved([])
               }
             ),
           );
         })
      |> map(relations => relations->List.flatten)
    };

  _network(synsetId, ~maxDepth, ());
};

let rec path = (synsetId: int, relationKind: Domain.relationKind, ~maxLength: option(int)=None, ()): Wordnet.jsRepromise(list(Domain.relation)) =>
  switch (maxLength) {
  | Some(0) => resolved([])
  | _ =>
    Wordnet.relationsForSynset(synsetId)
    |> andThen((relations: list(Domain.relation)) => {
         let filteredRelations =
           relations->List.keep(relation => relation.relationKind == relationKind)->List.keep(relation => relation.relTo == synsetId);

         Repromise.Rejectable.all(
           filteredRelations->List.map(relation =>
             path(relation.relFrom, relationKind, ~maxLength=maxLength->Option.map(d => d - 1), ())
             |> map(result => List.concat(filteredRelations, result))
           ),
         );
       })
    |> map(relations => relations->List.flatten)
  };