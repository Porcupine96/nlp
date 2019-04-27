[@bs.module "react-graph-vis"]
external component: ReasonReact.reactClass = "default";

type node = {
  .
  "id": int,
  "label": string,
};

type edge = {
  .
  "from": int,
  "to": int,
};

type props = {
  .
  graph: {
    .
    "nodes": array(node),
    "edges": array(edge),
  },
};

let make = (~nodes: array(node), ~edges: array(edge), children) => {
  let props = {
    "graph": {
      "nodes": nodes,
      "edges": edges,
    },
  };

  ReasonReact.wrapJsForReason(~reactClass=component, ~props, children);
};
