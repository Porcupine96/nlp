module Styles = {
  open Css;

  let root = style([height(px(100)), width(pct(90.))]);

  let paper =
    style([
      height(px(80)),
      width(pct(100.)),
      display(`flex),
      justifyContent(`center),
      alignItems(`center),
    ]);
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~description, _) => {
  ...component,
  render: _ =>
    <div className=Styles.root>
      <M.Paper className=Styles.paper> description </M.Paper>
    </div>,
};