// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Repromise = require("@aantron/repromise/src/js/repromise.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Wordnet$Wordnet = require("../infrastructure/Wordnet.bs.js");
var SynsetColumn$Wordnet = require("../components/SynsetColumn.bs.js");
var MaterialUi_Typography = require("@jsiebern/bs-material-ui/src/MaterialUi_Typography.bs.js");
var TaskDescription$Wordnet = require("../components/TaskDescription.bs.js");
var MaterialUi_CircularProgress = require("@jsiebern/bs-material-ui/src/MaterialUi_CircularProgress.bs.js");

var boldText = Css.style(/* :: */[
      Css.fontWeight(/* bold */-1055161979),
      /* [] */0
    ]);

var columnContainer = Css.style(/* :: */[
      Css.height(Css.pct(100)),
      /* :: */[
        Css.width(Css.pct(90)),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* :: */[
            Css.justifyContent(/* center */98248149),
            /* :: */[
              Css.marginTop(Css.rem(2)),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var progressContainer = Css.style(/* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.alignItems(/* center */98248149),
        /* :: */[
          Css.height(Css.rem(14)),
          /* [] */0
        ]
      ]
    ]);

var Styles = /* module */[
  /* boldText */boldText,
  /* columnContainer */columnContainer,
  /* progressContainer */progressContainer
];

function loadSynsets(send) {
  return Repromise.Rejectable[/* wait */6](send, Repromise.Rejectable[/* map */5]((function (synsets) {
                    return /* SynsetsLoaded */[synsets];
                  }), Repromise.Rejectable[/* andThen */4]((function (synsetIds) {
                        return Repromise.Rejectable[/* all */8](Belt_List.map(synsetIds, (function (synsetId) {
                                          return Repromise.Rejectable[/* map */5]((function (senses) {
                                                        return /* record */[
                                                                /* synsetId */synsetId,
                                                                /* senses */senses
                                                              ];
                                                      }), Wordnet$Wordnet.sensesForSynset(synsetId));
                                        })));
                      }), Repromise.Rejectable[/* andThen */4]((function (senses) {
                            return Repromise.Rejectable[/* all */8](Belt_List.map(senses, (function (sense) {
                                              return Wordnet$Wordnet.synsetForSenseId(sense[/* id */0]);
                                            })));
                          }), Wordnet$Wordnet.searchSenses("szkoda")))));
}

var initialState = /* record */[
  /* synsets : [] */0,
  /* ready */false
];

var component = ReasonReact.reducerComponent("One-Wordnet");

function make(param) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return loadSynsets(self[/* send */3]);
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var description = ReasonReact.element(undefined, undefined, TaskDescription$Wordnet.make(ReasonReact.element(undefined, undefined, MaterialUi_Typography.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[
                                "Find all meaning of the szkoda ",
                                React.createElement("b", undefined, " noun "),
                                "and display all their synonyms."
                              ])), /* array */[]));
              var columns = Belt_List.toArray(Belt_List.map(self[/* state */1][/* synsets */0], (function (synset) {
                          return ReasonReact.element(String(synset[/* synsetId */0]), undefined, SynsetColumn$Wordnet.make(synset, /* array */[]));
                        })));
              return React.createElement("div", undefined, description, React.createElement("div", {
                              className: columnContainer
                            }, self[/* state */1][/* ready */1] ? columns : React.createElement("div", {
                                    className: progressContainer
                                  }, ReasonReact.element(undefined, undefined, MaterialUi_CircularProgress.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[])))));
            }),
          /* initialState */(function (param) {
              return initialState;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, param) {
              return /* Update */Block.__(0, [/* record */[
                          /* synsets */action[0],
                          /* ready */true
                        ]]);
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.loadSynsets = loadSynsets;
exports.initialState = initialState;
exports.component = component;
exports.make = make;
/* boldText Not a pure module */
