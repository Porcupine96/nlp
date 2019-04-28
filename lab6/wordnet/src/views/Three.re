open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let depthPickerContainer = style([height(rem(3.)), width(pct(90.)), display(`flex)]);

  let depthPicker = style([width(rem(5.)), marginRight(rem(0.)), marginLeft(`auto)]);

  let graphContainer = style([height(rem(40.)), width(pct(90.)), display(`flex), justifyContent(`center)]);

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);
};

type action =
  | RelationsLoaded(list(Domain.relation), Belt_MapInt.t(Domain.synset))
  | DepthChanged(int);

type state = {
  relations: list(Domain.relation),
  synsetMap: Belt_MapInt.t(Domain.synset),
  depth: int,
  ready: bool,
};

let initialState = {relations: [], synsetMap: Belt_MapInt.empty, depth: 1, ready: false};

let loadRelations = (~depth: int, send: action => unit) => {
  Domain.(
    Wordnet.searchSenses("wypadek")
    |> map((senses) => (senses->List.keep(sense => sense.lemma == "wypadek" && sense.senseNumber == 1): list(Domain.sense)))
    |> map(senses => senses->List.headExn)
    |> andThen((sense: Domain.sense) => Wordnet.synsetForSenseId(sense.id))
    |> andThen(synsetId => Relations.path(synsetId, Domain.Hyponym, ~maxLength=Some(depth), ()))
    |> andThen((relations: list(Domain.relation)) =>
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
         |> map(synsetMap => RelationsLoaded(relations, synsetMap))
       )
    |> wait(send)
  );
};

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadRelations(~depth=self.state.depth, self.send),
  reducer: (action, state) =>
    switch (action) {
    | RelationsLoaded(relations, synsetMap) => ReasonReact.Update({...state, relations, synsetMap, ready: true})
    | DepthChanged(depth) => ReasonReact.UpdateWithSideEffects({...state, ready: false, depth}, self => loadRelations(~depth, self.send))
    },
  render: self => {
    let description =
      <TaskDescription
        description={
          <M.Typography>
            {ReasonReact.string("Find ")}
            {ReasonReact.string(self.state.depth == 1 ? "direct" : "second-order")}
            <b> {ReasonReact.string(" hyponyms ")} </b>
            {ReasonReact.string("of \"wypadek(1)\" noun")}
          </M.Typography>
        }
      />;

    let chooseDepth =
      <div className=Styles.depthPickerContainer>
        <M.Select
          className=Styles.depthPicker value={`Int(self.state.depth)} onChange={(_, update) => self.send(DepthChanged(update##props##value))}>
          <M.MenuItem value={`Int(1)}> {ReasonReact.string("1")} </M.MenuItem>
          <M.MenuItem value={`Int(2)}> {ReasonReact.string("2")} </M.MenuItem>
        </M.Select>
      </div>;

    let nodes: array(Graph.node) =
      self.state.relations
      ->Domain.distinctSynsets
      ->List.toArray
      ->Array.map(synsetId => {"id": synsetId, "label": Util.label(synsetId, self.state.synsetMap), "group": None});

    let edges: array(Graph.edge) =
      self.state.relations->List.map(relation => {"from": relation.relFrom, "to": relation.relTo, "label": None})->List.toArray;

    let options: Graph.options = {
      "nodes": {
        "shape": "dot",
        "size": 10,
        "shadow": true,
      },
      "edges": {
        "width": 1,
        "length": 100,
        "shadow": true,
        "smooth": {
          "type": "continuous",
        },
      },
    };

    let graph = <Graph nodes edges options />;

    <div>
      description
      chooseDepth
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