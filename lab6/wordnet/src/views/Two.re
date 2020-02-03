open Belt;
open Promise.Js;

module Styles = {
  open Css;

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);

  let graphContainer = style([height(rem(40.)), width(pct(90.)), display(`flex), justifyContent(`center)]);
};

type action =
  | RelationsLoaded(list(Domain.relation), Belt_MapInt.t(Domain.synset));

type state = {
  relations: list(Domain.relation),
  synsetMap: Belt_MapInt.t(Domain.synset),
  ready: bool,
};

let initialState = {relations: [], synsetMap: Belt_MapInt.empty, ready: false};

let loadRelations = (send: action => unit) =>
  Wordnet.searchSenses("wypadek drogowy")
  ->flatMap(senses => Promise.Js.all(List.map(senses, (sense: Domain.sense) => Wordnet.synsetForSenseId(sense.id))))
  ->flatMap(synsetIds => {
       let synsetId = synsetIds->List.headExn;
       Relations.path(synsetId, Domain.Hypernymy, ());
     })
  ->flatMap((relations: list(Domain.relation)) =>
       Promise.Js.all(
         relations
         ->Domain.distinctSynsets
         ->List.map(synsetId =>
             synsetId->Wordnet.sensesForSynset
             ->map(senses => {
                  let synset: Domain.synset = {synsetId, senses};
                  (synsetId, synset);
                })
           ),
       )
       ->map(synsets => synsets->List.toArray->Belt_MapInt.fromArray)
       ->map(synsetMap => RelationsLoaded(relations, synsetMap))
     )
  ->get(send);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadRelations(self.send),
  reducer: (action, _) =>
    switch (action) {
    | RelationsLoaded(relations, synsetMap) => ReasonReact.Update({relations, synsetMap, ready: true})
    },
  render: self => {
    let description =
      <TaskDescription
        description={
          <M.Typography>
            {ReasonReact.string("Find closure of")}
            <b> {ReasonReact.string(" hypernymy ")} </b>
            {ReasonReact.string(
               "relation for the first meaning of the \"wypadek drogowy\" expression. Create diagram of the relations as a directed graph.",
             )}
          </M.Typography>
        }
      />;

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
      "interaction": {
        "hideEdgesOnDrag": true,
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