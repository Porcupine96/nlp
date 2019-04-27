open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let progressContainer =
    style([display(`flex), alignItems(`center), height(rem(14.))]);

  let graphContainer =
    style([
      height(pct(100.)),
      width(pct(90.)),
      display(`flex),
      justifyContent(`center),
    ]);
};

type action =
  | RelationsLoaded(list(Domain.relation));

type state = {
  relations: list(Domain.relation),
  ready: bool,
};

let initialState = {relations: [], ready: false};

let loadRelations = (send: action => unit) => ();

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadRelations(self.send),
  reducer: (action, _) =>
    switch (action) {
    | RelationsLoaded(relations) =>
      Js.log(relations);
      ReasonReact.NoUpdate;
    },
  render: self => {
    let graph = <div />;

    <div>
      <TaskDescription>
        <M.Typography>
          {ReasonReact.string("Find closure of")}
          <b> {ReasonReact.string(" hypernymy ")} </b>
          {
            ReasonReact.string(
              "relation for the first meaning of the wypadek drogowy expression. Create diagram of the relations as a directed graph.",
            )
          }
        </M.Typography>
      </TaskDescription>
      <div className=Styles.graphContainer>
        {
          if (self.state.ready) {
            graph;
          } else {
            <div className=Styles.progressContainer>
              <M.CircularProgress />
            </div>;
          }
        }
      </div>
    </div>;
  },
};
