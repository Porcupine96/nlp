type route =
  | One
  | Two
  | Three
  | Four
  | Five
  | Six;

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => One
  | ["one"] => One
  | ["two"] => Two
  | ["three"] => Three
  | ["four"] => Four
  | ["five"] => Five
  | ["six"] => Six
  | _ => One
  };

let mapRouteToUrl = route =>
  switch (route) {
  | One => "/one"
  | Two => "/two"
  | Three => "/three"
  | Four => "/four"
  | Five => "/five"
  | Six => "/six"
  };

let navigate = route => ReasonReact.Router.push(mapRouteToUrl(route));

let getInitialRoute = () => {
  let route = ReasonReact.Router.dangerouslyGetInitialUrl()->mapUrlToRoute;
  ReasonReact.Router.push(mapRouteToUrl(route));
  route;
};
