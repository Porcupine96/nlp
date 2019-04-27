let component = ReasonReact.statelessComponent(__MODULE__);

module Styles = {
  open Css;
  let link = style([textDecoration(`none)]);
};

let make = (~route=?, ~className=?, children) => {
  ...component,
  render: _ => {
    let onClick = event => {
      event |> ReactEvent.Synthetic.preventDefault;
      Belt.Option.map(route, Router.navigate) |> ignore;
    };

    <a href="#" onClick className=Styles.link>
      {children |> ReasonReact.array}
    </a>;
  },
};
