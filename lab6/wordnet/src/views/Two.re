open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);

  let graphContainer = style([height(rem(30.)), width(pct(90.)), display(`flex), justifyContent(`center)]);
};

type action =
  | RelationsLoaded(list(Domain.relation), Belt_MapInt.t(Domain.synset));

type state = {
  relations: list(Domain.relation),
  synsetMap: Belt_MapInt.t(Domain.synset),
  ready: bool,
};

let initialState = {relations: [], synsetMap: Belt_MapInt.empty, ready: false};

let distinctSynsets = (relations: list(Domain.relation)) =>
  relations->List.map(relation => [relation.relFrom, relation.relTo])->List.flatten->List.toArray->Belt_SetInt.fromArray->Belt_SetInt.toList;

let label = (synsetId: int, synsetMap: Belt_MapInt.t(Domain.synset)): string =>
  switch (synsetMap->Belt_MapInt.get(synsetId)) {
  | Some(synset) => synset.senses->List.reduce("", (acc, sense) => acc == "" ? sense.lemma : acc ++ "\n" ++ sense.lemma)
  | None => string_of_int(synsetId)
  };

let loadRelations = (send: action => unit) =>
  Wordnet.searchSenses("wypadek drogowy")
  |> andThen(senses => Repromise.Rejectable.all(List.map(senses, (sense: Domain.sense) => Wordnet.synsetForSenseId(sense.id))))
  |> andThen(synsetIds => {
       let synsetId = synsetIds->List.headExn;
       Relations.path(synsetId, Domain.Hypernymy, ());
     })
  |> andThen((relations: list(Domain.relation)) =>
       Repromise.Rejectable.all(
         relations
         ->distinctSynsets
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
  |> wait(send);

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
      self.state.relations->distinctSynsets->List.toArray->Array.map(synsetId => {"id": synsetId, "label": label(synsetId, self.state.synsetMap)});

    let edges: array(Graph.edge) = self.state.relations->List.map(relation => {"from": relation.relFrom, "to": relation.relTo})->List.toArray;

    let graph = <Graph nodes edges />;

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