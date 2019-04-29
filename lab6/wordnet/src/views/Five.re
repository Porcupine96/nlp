open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let root = style([height(pct(90.))]);

  let setPickerContainer = style([height(rem(3.)), width(pct(90.)), display(`flex)]);

  let container = style([height(rem(6.)), width(pct(90.)), display(`flex)]);

  let distanceBlock =
    style([
      height(rem(6.)),
      width(rem(16.)),
      display(`flex),
      alignItems(`center),
      marginLeft(rem(0.)),
      marginRight(`auto),
      paddingLeft(rem(2.)),
    ]);

  let setPicker = style([width(rem(16.)), marginRight(rem(0.)), marginLeft(`auto)]);

  let graphContainer = style([height(pct(90.)), width(pct(90.)), display(`flex), justifyContent(`center)]);

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);
};

type action =
  | RelationsLoaded(list(int), list(Domain.relation), Belt_MapInt.t(Domain.synset))
  | LeftWordChosen(int)
  | RightWordChosen(int);

type state = {
  relations: list(Domain.relation),
  synsetIds: list(int),
  synsetMap: Belt_MapInt.t(Domain.synset),
  leftIndex: int,
  rightIndex: int,
  distance: option(float),
  ready: bool,
};

let initialState = {relations: [], synsetIds: [], synsetMap: Belt_MapInt.empty, leftIndex: 0, rightIndex: 1, distance: None, ready: false};

type numberedSense = {
  lemma: string,
  senseNumber: int,
};

let words = [|
  {lemma: {j|szkoda|j}, senseNumber: 2},
  {lemma: {j|wypadek|j}, senseNumber: 1},
  {lemma: {j|kolizja|j}, senseNumber: 1},
  {lemma: {j|kolizja|j}, senseNumber: 2},
  {lemma: {j|nieszczęście|j}, senseNumber: 2},
  {lemma: {j|katastrofa budowlana|j}, senseNumber: 1},
|];

let loadRelations = (~leftIndex: int, ~rightIndex: int, send: action => unit) =>
  all(
    [words->Array.getExn(leftIndex), words->Array.getExn(rightIndex)]
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
         ->List.map(synsetId =>
             synsetId |> (synsetId => Relations.network(synsetId, ~maxDepth=Some(2), ~relKinds=[|10, 11|]->Belt_SetInt.fromArray, ()))
           ),
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
  didMount: self => loadRelations(~leftIndex=self.state.leftIndex, ~rightIndex=self.state.rightIndex, self.send),
  reducer: (action, state) =>
    switch (action) {
    | RelationsLoaded(synsetIds, relations, synsetMap) =>
      let distance = Relations.shortestPathLength(synsetIds, relations)->Option.flatMap(shortestPath => LCH.calculate(~shortestPath, ()));
      ReasonReact.Update({...state, relations, synsetIds, synsetMap, distance, ready: true});
    | LeftWordChosen(leftIndex) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, leftIndex, ready: false},
        self => loadRelations(~leftIndex, ~rightIndex=self.state.rightIndex, self.send),
      )
    | RightWordChosen(rightIndex) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, rightIndex, ready: false},
        self => loadRelations(~leftIndex=self.state.leftIndex, ~rightIndex, self.send),
      )
    },
  render: self => {
    let description =
      <TaskDescription
        description={
          <M.Typography> {ReasonReact.string("Display as a directed graph semantic relations between the groups of lexemes.")} </M.Typography>
        }
      />;

    let distanceBlock =
      <M.Paper className=Styles.distanceBlock>
        <M.Typography>
          {ReasonReact.string(
             "Leacock Chodorow: "
             ++ (
               switch (self.state.distance) {
               | Some(dist) => dist |> Js.Float.toFixedWithPrecision(~digits=5)
               | None => "?"
               }
             ),
           )}
        </M.Typography>
      </M.Paper>;

    let chooseWord = (index: int, onChange: int => unit) => {
      <div className=Styles.setPickerContainer>
        <M.Select className=Styles.setPicker value={`Int(index)} onChange={(_, update) => onChange(update##props##value)}>
          {words
           ->Array.zip(Array.range(0, Array.length(words)))
           ->Array.map(((word, index)) =>
               <M.MenuItem value={`Int(index)}> {ReasonReact.string(word.lemma ++ " (" ++ string_of_int(word.senseNumber) ++ ")")} </M.MenuItem>
             )}
        </M.Select>
      </div>;
    };

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
      <div className=Styles.container>
        distanceBlock
        <div>
          {chooseWord(self.state.leftIndex, wordIndex => self.send(LeftWordChosen(wordIndex)))}
          {chooseWord(self.state.rightIndex, wordIndex => self.send(RightWordChosen(wordIndex)))}
        </div>
      </div>
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