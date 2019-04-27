open Belt;
open Repromise.Rejectable;

let rec traverseRelations =
        (
          synsetId: int,
          relationKind: Domain.relationKind,
          visitedSynsets: list(int),
          ~maxDepth: option(int)=Some(5),
          ~target: option(int)=None,
          (),
        )
        : Wordnet.jsRepromise(list(Domain.relation)) =>
  switch (maxDepth) {
  | Some(0) => resolved([])
  | _ =>
    Wordnet.relationsForSynset(synsetId)
    |> andThen((relations: list(Domain.relation)) => {
         let filteredRelations = relations->List.keep(relation => relation.relationKind == relationKind);
         Js.log(synsetId);
         Js.log(filteredRelations->List.toArray);

         Repromise.Rejectable.all(
           filteredRelations->List.map(relation =>
             switch (relation.relFrom, relation.relTo) {
             | (relFrom, relTo)
                 when relFrom == synsetId && !visitedSynsets->List.has(relTo, (==)) && target->Option.map(t => t == relTo) != Some(false) =>
               Js.log("A");
               traverseRelations(
                 relTo,
                 relationKind,
                 [relTo, ...visitedSynsets],
                 ~maxDepth=maxDepth->Option.map(d => d - 1),
                 ~target=Some(relFrom),
                 (),
               )
               |> map(result => List.concat(filteredRelations, result));
             | (relFrom, relTo)
                 when relTo == synsetId && !visitedSynsets->List.has(relFrom, (==)) && target->Option.map(t => t == relFrom) != Some(false) =>
               Js.log("B");
               traverseRelations(
                 relFrom,
                 relationKind,
                 [relFrom, ...visitedSynsets],
                 ~maxDepth=maxDepth->Option.map(d => d - 1),
                 ~target=Some(relTo),
                 (),
               )
               |> map(result => List.concat(filteredRelations, result));
             | _ => resolved([])
             }
           ),
         );
       })
    |> map(relations => relations->List.flatten)
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