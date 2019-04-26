open MaterialUi;

module Styles = {
  open Css;

  let container = style([height(pct(100.))]);
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make = _ => {
  ...component,
  render: _ =>
    <div className=Styles.container> <Layout> <One /> </Layout> </div>,
};
