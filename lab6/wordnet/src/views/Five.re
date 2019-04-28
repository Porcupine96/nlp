open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let graphContainer = style([height(rem(40.)), width(pct(90.)), display(`flex), justifyContent(`center)]);

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);
};

type action =
  | RelationsLoaded(list(Domain.relation), Belt_MapInt.t(Domain.synset));

type state = {
  relations: list(Domain.relation),
  synsetMap: Belt_MapInt.t(Domain.synset),
  ready: bool,
};

let initialState = {relations: [], synsetMap: Belt_MapInt.empty, ready: false};

type numberedSense = {
  lemma: string,
  senseNumber: int,
};

let numberedSenses = [{lemma: {j|szkoda|j}, senseNumber: 2}, {lemma: {j|wypadek|j}, senseNumber: 1}];

let loadRelations = (send: action => unit) =>
  all(
    numberedSenses->List.map(sense =>
      Wordnet.searchSenses(sense.lemma)
      |> map((senses: list(Domain.sense)) => senses->List.keep(s => s.lemma == sense.lemma && s.senseNumber == sense.senseNumber))
      |> map(senses => senses->List.headExn)
      |> andThen((sense: Domain.sense) => Wordnet.synsetForSenseId(sense.id))
    ),
  )
  |> andThen(synsetIds =>
       all(
         synsetIds
         ->List.toArray
         ->Belt_SetInt.fromArray
         ->Belt_SetInt.toList
         ->List.map(synsetId => synsetId |> (synsetId => Relations.network(synsetId, ~maxDepth=Some(2), ()))),
       )
       |> map((relations: list(list(Domain.relation))) => (synsetIds, relations))
     )
  |> map(((synsetIds, relations)) =>
       (synsetIds, relations->List.flatten->List.toArray->Belt_Set.fromArray(~id=(module Domain.RelationCmp))->Belt_Set.toList)
     )
  |> andThen(((synsetIds, relations)) =>
       Repromise.Rejectable.all(
         synsetIds->List.map(synsetId =>
           synsetId->Wordnet.sensesForSynset
           |> map(senses => {
                let synset: Domain.synset = {synsetId, senses};
                (synsetId, synset);
              })
         ),
       )
       |> map(synsets => synsets->List.toArray->Belt_MapInt.fromArray)
       |> map(synsetMap => RelationsLoaded(relations, synsetMap))
     )
  |> wait(send);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadRelations(self.send),
  reducer: (action, _) =>
    switch (action) {
    | RelationsLoaded(relations, synsetMap) =>
      Js.log("loaded");
      Js.log(relations->List.toArray);
      ReasonReact.Update({relations, synsetMap, ready: true});
    },
  render: self => {
    let description =
      <TaskDescription
        description={
          <M.Typography> {ReasonReact.string("Display as a directed graph semantic relations between the groups of lexemes.")} </M.Typography>
        }
      />;

    let nodes: array(Graph.node) =
      self.state.synsetMap
      ->Belt_MapInt.valuesToArray
      ->Array.map(synset => {"id": synset.synsetId, "label": Util.label(synset.synsetId, self.state.synsetMap), "group": None});

    let edges: array(Graph.edge) =
      self.state.relations
      ->List.map(relation => {"from": relation.relFrom, "to": relation.relTo, "label": Some(relation.relationName)})
      ->List.toArray;

    let options: Graph.options = {
      "nodes": {
        "shape": "dot",
        "size": 10,
        "shadow": true,
      },
      "edges": {
        "width": 1,
        "length": 200,
        "shadow": true,
        "smooth": {
          "type": "dynamic",
        },
      },
    };

    let graph = <Graph nodes edges options />;

    <div>
      description
      <div className=Styles.graphContainer>
        {if (self.state.ready) {
           graph;
         } else {
           <div className=Styles.progressContainer> <M.CircularProgress /> </div>;
         }}
      </div>
    </div>;
  },
};