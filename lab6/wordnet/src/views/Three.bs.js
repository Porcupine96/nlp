// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Repromise = require("@aantron/repromise/src/js/repromise.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_MapInt = require("bs-platform/lib/js/belt_MapInt.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Util$Wordnet = require("../infrastructure/Util.bs.js");
var Graph$Wordnet = require("../infrastructure/Graph.bs.js");
var Domain$Wordnet = require("../domain/Domain.bs.js");
var Wordnet$Wordnet = require("../infrastructure/Wordnet.bs.js");
var MaterialUi_Select = require("@jsiebern/bs-material-ui/src/MaterialUi_Select.bs.js");
var Relations$Wordnet = require("../domain/Relations.bs.js");
var MaterialUi_MenuItem = require("@jsiebern/bs-material-ui/src/MaterialUi_MenuItem.bs.js");
var MaterialUi_Typography = require("@jsiebern/bs-material-ui/src/MaterialUi_Typography.bs.js");
var TaskDescription$Wordnet = require("../components/TaskDescription.bs.js");
var MaterialUi_CircularProgress = require("@jsiebern/bs-material-ui/src/MaterialUi_CircularProgress.bs.js");

var boldText = Css.style(/* :: */[
      Css.fontWeight(/* bold */-1055161979),
      /* [] */0
    ]);

var depthPickerContainer = Css.style(/* :: */[
      Css.height(Css.rem(3)),
      /* :: */[
        Css.width(Css.pct(90)),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* [] */0
        ]
      ]
    ]);

var depthPicker = Css.style(/* :: */[
      Css.width(Css.rem(5)),
      /* :: */[
        Css.marginRight(Css.rem(0)),
        /* :: */[
          Css.marginLeft(/* auto */-1065951377),
          /* [] */0
        ]
      ]
    ]);

var graphContainer = Css.style(/* :: */[
      Css.height(Css.rem(40)),
      /* :: */[
        Css.width(Css.pct(90)),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* :: */[
            Css.justifyContent(/* center */98248149),
            /* [] */0
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
  /* depthPickerContainer */depthPickerContainer,
  /* depthPicker */depthPicker,
  /* graphContainer */graphContainer,
  /* progressContainer */progressContainer
];

var initialState = /* record */[
  /* relations : [] */0,
  /* synsetMap */Belt_MapInt.empty,
  /* depth */1,
  /* ready */false
];

function loadRelations(depth, send) {
  return Repromise.Rejectable[/* wait */6](send, Repromise.Rejectable[/* andThen */4]((function (relations) {
                    return Repromise.Rejectable[/* map */5]((function (synsetMap) {
                                  return /* RelationsLoaded */Block.__(0, [
                                            relations,
                                            synsetMap
                                          ]);
                                }), Repromise.Rejectable[/* map */5]((function (synsets) {
                                      return Belt_MapInt.fromArray(Belt_List.toArray(synsets));
                                    }), Repromise.Rejectable[/* all */8](Belt_List.map(Domain$Wordnet.distinctSynsets(relations), (function (synsetId) {
                                              return Repromise.Rejectable[/* map */5]((function (senses) {
                                                            var synset = /* record */[
                                                              /* synsetId */synsetId,
                                                              /* senses */senses
                                                            ];
                                                            return /* tuple */[
                                                                    synsetId,
                                                                    synset
                                                                  ];
                                                          }), Wordnet$Wordnet.sensesForSynset(synsetId));
                                            })))));
                  }), Repromise.Rejectable[/* andThen */4]((function (synsetId) {
                        return Relations$Wordnet.path(synsetId, /* Hyponym */0, Caml_option.some(depth), /* () */0);
                      }), Repromise.Rejectable[/* andThen */4]((function (sense) {
                            return Wordnet$Wordnet.synsetForSenseId(sense[/* id */0]);
                          }), Repromise.Rejectable[/* map */5](Belt_List.headExn, Repromise.Rejectable[/* map */5]((function (senses) {
                                    return Belt_List.keep(senses, (function (sense) {
                                                  if (sense[/* lemma */1] === "wypadek") {
                                                    return sense[/* senseNumber */3] === 1;
                                                  } else {
                                                    return false;
                                                  }
                                                }));
                                  }), Wordnet$Wordnet.searchSenses("wypadek")))))));
}

var component = ReasonReact.reducerComponent("Three-Wordnet");

function make(param) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return loadRelations(self[/* state */1][/* depth */2], self[/* send */3]);
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var match = self[/* state */1][/* depth */2] === 1;
              var description = ReasonReact.element(undefined, undefined, TaskDescription$Wordnet.make(ReasonReact.element(undefined, undefined, MaterialUi_Typography.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[
                                "Find ",
                                match ? "direct" : "second-order",
                                React.createElement("b", undefined, " hyponyms "),
                                "of \"wypadek(1)\" noun"
                              ])), /* array */[]));
              var chooseDepth = React.createElement("div", {
                    className: depthPickerContainer
                  }, ReasonReact.element(undefined, undefined, MaterialUi_Select.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, (function (param, update) {
                              return Curry._1(self[/* send */3], /* DepthChanged */Block.__(1, [update.props.value]));
                            }), undefined, undefined, undefined, undefined, undefined, /* `Int */[
                            3654863,
                            self[/* state */1][/* depth */2]
                          ], undefined, undefined, undefined, depthPicker, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[
                            ReasonReact.element(undefined, undefined, MaterialUi_MenuItem.make(undefined, undefined, undefined, undefined, undefined, /* `Int */[
                                      3654863,
                                      1
                                    ], undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */["1"])),
                            ReasonReact.element(undefined, undefined, MaterialUi_MenuItem.make(undefined, undefined, undefined, undefined, undefined, /* `Int */[
                                      3654863,
                                      2
                                    ], undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */["2"]))
                          ])));
              var nodes = Belt_Array.map(Belt_List.toArray(Domain$Wordnet.distinctSynsets(self[/* state */1][/* relations */0])), (function (synsetId) {
                      return {
                              id: synsetId,
                              label: Util$Wordnet.label(synsetId, self[/* state */1][/* synsetMap */1]),
                              group: undefined
                            };
                    }));
              var edges = Belt_List.toArray(Belt_List.map(self[/* state */1][/* relations */0], (function (relation) {
                          return {
                                  from: relation[/* relFrom */1],
                                  to: relation[/* relTo */2],
                                  label: undefined
                                };
                        })));
              var options = {
                nodes: {
                  shape: "dot",
                  size: 10,
                  shadow: true
                },
                edges: {
                  width: 1,
                  length: 100,
                  shadow: true,
                  smooth: {
                    type: "continuous"
                  }
                },
                interaction: {
                  hideEdgesOnDrag: true
                }
              };
              var graph = ReasonReact.element(undefined, undefined, Graph$Wordnet.make(nodes, edges, options, /* array */[]));
              return React.createElement("div", undefined, description, chooseDepth, React.createElement("div", {
                              className: graphContainer
                            }, self[/* state */1][/* ready */3] ? graph : React.createElement("div", {
                                    className: progressContainer
                                  }, ReasonReact.element(undefined, undefined, MaterialUi_CircularProgress.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[])))));
            }),
          /* initialState */(function (param) {
              return initialState;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (action.tag) {
                var depth = action[0];
                return /* UpdateWithSideEffects */Block.__(2, [
                          /* record */[
                            /* relations */state[/* relations */0],
                            /* synsetMap */state[/* synsetMap */1],
                            /* depth */depth,
                            /* ready */false
                          ],
                          (function (self) {
                              return loadRelations(depth, self[/* send */3]);
                            })
                        ]);
              } else {
                return /* Update */Block.__(0, [/* record */[
                            /* relations */action[0],
                            /* synsetMap */action[1],
                            /* depth */state[/* depth */2],
                            /* ready */true
                          ]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.initialState = initialState;
exports.loadRelations = loadRelations;
exports.component = component;
exports.make = make;
/* boldText Not a pure module */
