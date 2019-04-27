[@bs.module "react-graph-vis"] external component: ReasonReact.reactClass = "default";

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

type options = {
  .
  "nodes": {
    .
    "shape": string,
    "size": int,
    "shadow": bool,
  },
  "edges": {
    .
    "width": int,
    "shadow": bool,
    "smooth": {. "type": string},
  },
};

type props = {
  .
  graph: {
    .
    "nodes": array(node),
    "edges": array(edge),
  },
};

let make = (~nodes: array(node), ~edges: array(edge), ~options: options, children) => {
  let props = {
    "graph": {
      "nodes": nodes,
      "edges": edges,
      "options": options,
    },
  };

  ReasonReact.wrapJsForReason(~reactClass=component, ~props, children);
};