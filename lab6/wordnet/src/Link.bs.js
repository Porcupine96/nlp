// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var React = require("react");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Router$Wordnet = require("./Router.bs.js");

var component = ReasonReact.statelessComponent("Link-Wordnet");

var link = Css.style(/* :: */[
      Css.textDecoration(/* none */-922086728),
      /* [] */0
    ]);

var Styles = /* module */[/* link */link];

function make(route, className, children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (param) {
              var onClick = function ($$event) {
                $$event.preventDefault();
                Belt_Option.map(route, Router$Wordnet.navigate);
                return /* () */0;
              };
              return React.createElement("a", {
                          className: link,
                          href: "#",
                          onClick: onClick
                        }, children);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.Styles = Styles;
exports.make = make;
/* component Not a pure module */
