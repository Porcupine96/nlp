open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let columnContainer =
    style([width(pct(90.)), display(`flex), justifyContent(`center)]);
};

type action =
  | SynsetsLoaded(list(Domain.synset));

type state = {synsets: list(Domain.synset)};

let loadSynsets = (send: action => unit) =>
  Wordnet.searchSenses("szkoda")
  |> andThen(senses =>
       Repromise.Rejectable.all(
         List.map(senses, (sense: Domain.sense) =>
           Wordnet.synsetForSenseId(sense.id)
         ),
       )
     )
  |> andThen(synsetIds =>
       Repromise.Rejectable.all(
         synsetIds
         ->List.map(synsetId =>
             Wordnet.sensesForSynset(synsetId)
             |> map(senses => Domain.{synsetId, senses})
           ),
       )
     )
  |> map(synsets => SynsetsLoaded(synsets))
  |> wait(send);

let initialState = {synsets: []};

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadSynsets(self.send),
  reducer: (action, _) =>
    switch (action) {
    | SynsetsLoaded(synsets) => ReasonReact.Update({synsets: synsets})
    },
  render: self => {
    let columns =
      self.state.synsets
      ->List.map(synset =>
          <SynsetColumn key={string_of_int(synset.synsetId)} synset />
        )
      ->List.toArray
      ->ReasonReact.array;

    <div>
      <TaskDescription>
        <M.Typography>
          {ReasonReact.string("Find all meaning of the szkoda ")}
          {ReasonReact.string(" noun ")}
          {ReasonReact.string("and display all their synonyms.")}
        </M.Typography>
      </TaskDescription>
      <div className=Styles.columnContainer> columns </div>
    </div>;
  },
};
