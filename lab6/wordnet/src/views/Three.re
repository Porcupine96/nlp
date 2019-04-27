open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let graphContainer = style([height(pct(100.)), width(pct(90.)), display(`flex), justifyContent(`center)]);

  let progressContainer = style([display(`flex), alignItems(`center), height(rem(14.))]);
};

let setup = () => {
  Wordnet.searchSenses("wypadek") |> wait(res => Js.log(res->List.toArray));
};

type state = {ready: bool};

type action =
  | A;

let initialState = {ready: false};

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => setup(),
  reducer: (action: action, state: state) => ReasonReact.NoUpdate,
  render: self => {
    let description =
      <TaskDescription
        description={
          <M.Typography>
            {ReasonReact.string("Find direct ")}
            <b> {ReasonReact.string(" hyponyms ")} </b>
            {ReasonReact.string("of \"wypadek(1)\" noun")}
          </M.Typography>
        }
      />;

    let graph = <div />;

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