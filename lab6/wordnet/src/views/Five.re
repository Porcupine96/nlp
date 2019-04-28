open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let root = style([height(pct(90.))]);

  let setPickerContainer = style([height(rem(3.)), width(pct(90.)), display(`flex)]);

  let setPicker = style([width(rem(5.)), marginRight(rem(0.)), marginLeft(`auto)]);

  let graphContainer = style([height(pct(90.)), width(pct(90.)), display(`flex), justifyContent(`center)]);

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);
};

type action =
  | RelationsLoaded(list(int), list(Domain.relation), Belt_MapInt.t(Domain.synset))
  | SetChanged(int);

type state = {
  relations: list(Domain.relation),
  synsetIds: list(int),
  synsetMap: Belt_MapInt.t(Domain.synset),
  setIndex: int,
  ready: bool,
};

let initialState = {relations: [], synsetIds: [], synsetMap: Belt_MapInt.empty, setIndex: 1, ready: false};

type numberedSense = {
  lemma: string,
  senseNumber: int,
};

let setOne = [{lemma: {j|szkoda|j}, senseNumber: 2}, {lemma: {j|wypadek|j}, senseNumber: 1}];

let setTwo = [];

let setForIndex = (index: int) =>
  switch (index) {
  | 1 => setOne
  | _ => setTwo
  };

let loadRelations = (~setIndex: int, send: action => unit) =>
  all(
    setForIndex(setIndex)
    ->List.map(sense =>
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
  |> andThen(((synsetIds, relations)) => {
       let distinctSynsetIds = synsetIds->List.toArray->Belt_SetInt.fromArray->Belt_SetInt.toList;

       Repromise.Rejectable.all(
         relations
         ->Domain.distinctSynsets
         ->List.map(synsetId =>
             synsetId->Wordnet.sensesForSynset
             |> map(senses => {
                  let synset: Domain.synset = {synsetId, senses};
                  (synsetId, synset);
                })
           ),
       )
       |> map(synsets => synsets->List.toArray->Belt_MapInt.fromArray)
       |> map(synsetMap => RelationsLoaded(distinctSynsetIds, relations, synsetMap));
     })
  |> wait(send);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadRelations(~setIndex=self.state.setIndex, self.send),
  reducer: (action, state) =>
    switch (action) {
    | RelationsLoaded(synsetIds, relations, synsetMap) => ReasonReact.Update({...state, relations, synsetIds, synsetMap, ready: true})
    | SetChanged(setIndex) => ReasonReact.UpdateWithSideEffects({...state, setIndex, ready: false}, self => loadRelations(~setIndex, self.send))
    },
  render: self => {
    let description =
      <TaskDescription
        description={
          <M.Typography> {ReasonReact.string("Display as a directed graph semantic relations between the groups of lexemes.")} </M.Typography>
        }
      />;

    let chooseSet =
      <div className=Styles.setPickerContainer>
        <M.Select
          className=Styles.setPicker value={`Int(self.state.setIndex)} onChange={(_, update) => self.send(SetChanged(update##props##value))}>
          <M.MenuItem value={`Int(1)}> {ReasonReact.string("Set 1")} </M.MenuItem>
          <M.MenuItem value={`Int(2)}> {ReasonReact.string("Set 2")} </M.MenuItem>
        </M.Select>
      </div>;

    let mainNodes: array(Graph.node) =
      self.state.synsetIds
      ->List.toArray
      ->Array.map(synsetId => {"id": synsetId, "label": Util.label(synsetId, self.state.synsetMap), "group": Some(1)});

    let sideNodes: array(Graph.node) =
      Relations.closure(self.state.synsetIds, self.state.relations)
      ->List.toArray
      ->Array.map(synsetId => {"id": synsetId, "label": Util.label(synsetId, self.state.synsetMap), "group": Some(2)});

    let nodes = Array.concat(mainNodes, sideNodes);

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

    <div className=Styles.root>
      description
      chooseSet
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