// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var MaterialUi_Paper = require("@jsiebern/bs-material-ui/src/MaterialUi_Paper.bs.js");
var MaterialUi_Table = require("@jsiebern/bs-material-ui/src/MaterialUi_Table.bs.js");
var MaterialUi_TableRow = require("@jsiebern/bs-material-ui/src/MaterialUi_TableRow.bs.js");
var MaterialUi_TableBody = require("@jsiebern/bs-material-ui/src/MaterialUi_TableBody.bs.js");
var MaterialUi_TableCell = require("@jsiebern/bs-material-ui/src/MaterialUi_TableCell.bs.js");
var MaterialUi_TableHead = require("@jsiebern/bs-material-ui/src/MaterialUi_TableHead.bs.js");

var root = Css.style(/* :: */[
      Css.width(Css.pct(33)),
      /* :: */[
        Css.marginLeft(Css.px(10)),
        /* :: */[
          Css.marginRight(Css.px(10)),
          /* [] */0
        ]
      ]
    ]);

var Styles = /* module */[/* root */root];

var component = ReasonReact.statelessComponent("SynsetColumn-Wordnet");

function make(synset, param) {
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
              var header = ReasonReact.element(undefined, undefined, MaterialUi_TableRow.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[ReasonReact.element(undefined, undefined, MaterialUi_TableCell.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */["synset: " + String(synset[/* synsetId */0])]))]));
              var rows = Belt_Array.map(Belt_List.toArray(synset[/* senses */1]), (function (sense) {
                      return ReasonReact.element(String(sense[/* id */0]), undefined, MaterialUi_TableRow.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[ReasonReact.element(undefined, undefined, MaterialUi_TableCell.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[sense[/* lemma */1] + (" (" + (sense[/* partOfSpeech */2] + ")"))]))]));
                    }));
              return ReasonReact.element(undefined, undefined, MaterialUi_Paper.make(root, undefined, undefined, undefined, undefined, undefined, /* array */[ReasonReact.element(undefined, undefined, MaterialUi_Table.make(undefined, undefined, undefined, undefined, undefined, /* array */[
                                        ReasonReact.element(undefined, undefined, MaterialUi_TableHead.make(undefined, undefined, undefined, undefined, /* array */[header])),
                                        ReasonReact.element(undefined, undefined, MaterialUi_TableBody.make(undefined, undefined, undefined, undefined, /* array */[rows]))
                                      ]))]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* root Not a pure module */
