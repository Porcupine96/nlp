open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let columnContainer = style([height(pct(100.)), width(pct(90.)), display(`flex), justifyContent(`center), marginTop(rem(2.))]);

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);
};

type action =
  | SynsetsLoaded(list(Domain.synset));

type state = {
  synsets: list(Domain.synset),
  ready: bool,
};

let loadSynsets = (send: action => unit) =>
  Wordnet.searchSenses("szkoda")
  |> andThen(senses => Repromise.Rejectable.all(List.map(senses, (sense: Domain.sense) => Wordnet.synsetForSenseId(sense.id))))
  |> andThen(synsetIds =>
       Repromise.Rejectable.all(synsetIds->List.map(synsetId => Wordnet.sensesForSynset(synsetId) |> map(senses => Domain.{synsetId, senses})))
     )
  |> map(synsets => SynsetsLoaded(synsets))
  |> wait(send);

let initialState = {synsets: [], ready: false};

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadSynsets(self.send),
  reducer: (action, _) =>
    switch (action) {
    | SynsetsLoaded(synsets) => ReasonReact.Update({ready: true, synsets})
    },
  render: self => {
    let description =
      <TaskDescription
        description={
          <M.Typography>
            {ReasonReact.string("Find all meaning of the szkoda ")}
            <b> {ReasonReact.string(" noun ")} </b>
            {ReasonReact.string("and display all their synonyms.")}
          </M.Typography>
        }
      />;

    let columns =
      self.state.synsets->List.map(synset => <SynsetColumn key={string_of_int(synset.synsetId)} synset />)->List.toArray->ReasonReact.array;

    <div>
      description
      <div className=Styles.columnContainer>
        {if (self.state.ready) {
           columns;
         } else {
           <div className=Styles.progressContainer> <M.CircularProgress /> </div>;
         }}
      </div>
    </div>;
  },
};