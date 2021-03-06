module Styles = {
  open Css;

  let container = style([height(pct(100.))]);
};

type action =
  | UpdateRoute(Router.route);

type state = {route: Router.route};

let initialState: state = {route: One};

let component = ReasonReact.reducerComponent(__MODULE__);

let routeToComponent = route =>
  Router.(
    switch (route) {
    | One => <One key="1" />
    | Two => <Two key="2" />
    | Three => <Three key="3" />
    | Four => <Four key="4" />
    | Five => <Five key="5" />
    }
  );

let make = _ => {
  ...component,
  initialState: () => initialState,
  reducer: (action, _) =>
    switch (action) {
    | UpdateRoute(route) => ReasonReact.Update({route: route})
    },
  didMount: self => {
    let watcherId = ReasonReact.Router.watchUrl(url => url->Router.mapUrlToRoute->UpdateRoute->(self.send));

    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  render: self => <div className=Styles.container> <Layout> {routeToComponent(self.state.route)} </Layout> </div>,
};