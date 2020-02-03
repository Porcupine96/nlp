open Belt;
open Promise.Js;

let network =
    (synsetId: int, ~maxDepth: option(int)=Some(1), ~relKinds: option(Belt_SetInt.t)=?, ()): Wordnet.jsPromise(list(Domain.relation)) => {
  let visited = ref(Belt_SetInt.empty);
  let relationIds = ref(Belt_SetInt.empty);

  let rec _network = (synsetId: int, ~maxDepth: option(int)=Some(1), ()) =>
    switch (maxDepth) {
    | Some(0) => resolved([])
    | _ =>
      Wordnet.relationsForSynset(synsetId)
      ->flatMap((relations: list(Domain.relation)) => {
           let allowedRelations =
             relKinds
             ->Option.map(allowed => relations->List.keep(relation => allowed->Belt_SetInt.has(Domain.(relation.relationId))))
             ->Option.getWithDefault(relations);

           let newRelations = allowedRelations->List.keep(relation => !(relationIds^)->Belt_SetInt.has(relation.id));
           newRelations->List.forEach(relation => relationIds := (relationIds^)->Belt_SetInt.add(relation.id));

           Promise.Js.all(
             newRelations->List.map(relation =>
               switch (relation.relFrom, relation.relTo) {
               | (relFrom, relTo) when relFrom == synsetId && !(visited^)->Belt_SetInt.has(relTo) =>
                 visited := (visited^)->Belt_SetInt.add(relTo);
                 _network(relTo, ~maxDepth=maxDepth->Option.map(d => d - 1), ())->map(result => List.concat(newRelations, result));
               | (relFrom, relTo) when relTo == synsetId && !(visited^)->Belt_SetInt.has(relFrom) =>
                 visited := (visited^)->Belt_SetInt.add(relFrom);
                 _network(relFrom, ~maxDepth=maxDepth->Option.map(d => d - 1), ())->map(result => List.concat(newRelations, result));
               | _ => resolved([])
               }
             ),
           );
         })
      ->map(relations => relations->List.flatten)
    };

  _network(synsetId, ~maxDepth, ());
};

let rec path = (synsetId: int, relationKind: Domain.relationKind, ~maxLength: option(int)=None, ()): Wordnet.jsPromise(list(Domain.relation)) =>
  switch (maxLength) {
  | Some(0) => resolved([])
  | _ =>
    Wordnet.relationsForSynset(synsetId)
    ->flatMap((relations: list(Domain.relation)) => {
         let filteredRelations =
           relations->List.keep(relation => relation.relationKind == relationKind)->List.keep(relation => relation.relTo == synsetId);

         Promise.Js.all(
           filteredRelations->List.map(relation =>
             path(relation.relFrom, relationKind, ~maxLength=maxLength->Option.map(d => d - 1), ())
             ->map(result => List.concat(filteredRelations, result))
           ),
         );
       })
    ->map(relations => relations->List.flatten)
  };

let nodesInPath = (a: int, b: int, relations: list(Domain.relation)) => {
  let visited = ref(Belt_SetInt.empty);

  let rec _search = (currentNode: int, route: list(int)) =>
    if (currentNode == b) {
      route;
    } else {
      let updatedRoute = route->List.add(currentNode);
      visited := (visited^)->Belt_SetInt.add(currentNode);

      relations
      ->List.map(relation =>
          switch (relation.relFrom, relation.relTo) {
          | (relFrom, relTo) when relFrom == currentNode && !(visited^)->Belt_SetInt.has(relTo) => _search(relTo, updatedRoute)
          | (relFrom, relTo) when relTo == currentNode && !(visited^)->Belt_SetInt.has(relFrom) => _search(relFrom, updatedRoute)
          | _ => []
          }
        )
      ->List.flatten;
    };

  _search(a, []);
};

let closure = (synsetIds: list(int), relations: list(Domain.relation)) => {
  synsetIds
  ->List.map(a => synsetIds->List.map(b => (a, b))->List.keep(((a, b)) => a != b))
  ->List.flatten
  ->List.map(((a, b)) => nodesInPath(a, b, relations))
  ->List.flatten
  ->List.keep(synsetId => !synsetIds->List.has(synsetId, (==)))
  ->List.toArray
  ->Belt_SetInt.fromArray
  ->Belt_SetInt.toList;
};

let shortestPathLength = (synsetIds: list(int), relations: list(Domain.relation)) => {
  synsetIds
  ->List.map(a => synsetIds->List.map(b => (a, b))->List.keep(((a, b)) => a != b))
  ->List.flatten
  ->List.map(((a, b)) => nodesInPath(a, b, relations))
  ->List.sort((a, b) => List.length(a) - List.length(b))
  ->List.head
  ->Option.map(path => List.length(path) / 2);
};