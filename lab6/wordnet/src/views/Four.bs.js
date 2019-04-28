// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var Belt_Set = require("bs-platform/lib/js/belt_Set.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Repromise = require("@aantron/repromise/src/js/repromise.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_MapInt = require("bs-platform/lib/js/belt_MapInt.js");
var Belt_SetInt = require("bs-platform/lib/js/belt_SetInt.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Util$Wordnet = require("../infrastructure/Util.bs.js");
var Graph$Wordnet = require("../infrastructure/Graph.bs.js");
var Domain$Wordnet = require("../domain/Domain.bs.js");
var Wordnet$Wordnet = require("../infrastructure/Wordnet.bs.js");
var Relations$Wordnet = require("../domain/Relations.bs.js");
var MaterialUi_Typography = require("@jsiebern/bs-material-ui/src/MaterialUi_Typography.bs.js");
var TaskDescription$Wordnet = require("../components/TaskDescription.bs.js");
var MaterialUi_CircularProgress = require("@jsiebern/bs-material-ui/src/MaterialUi_CircularProgress.bs.js");

var boldText = Css.style(/* :: */[
      Css.fontWeight(/* bold */-1055161979),
      /* [] */0
    ]);

var root = Css.style(/* :: */[
      Css.height(Css.pct(90)),
      /* [] */0
    ]);

var graphContainer = Css.style(/* :: */[
      Css.height(Css.pct(90)),
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
  /* root */root,
  /* graphContainer */graphContainer,
  /* progressContainer */progressContainer
];

var initialState = /* record */[
  /* relations : [] */0,
  /* synsetMap */Belt_MapInt.empty,
  /* ready */false
];

var numberedSenses = /* :: */[
  /* record */[
    /* lemma */"wypadek",
    /* senseNumber */1
  ],
  /* :: */[
    /* record */[
      /* lemma */"wypadek komunikacyjny",
      /* senseNumber */1
    ],
    /* :: */[
      /* record */[
        /* lemma */"kolizja",
        /* senseNumber */2
      ],
      /* :: */[
        /* record */[
          /* lemma */"zderzenie",
          /* senseNumber */2
        ],
        /* :: */[
          /* record */[
            /* lemma */"kolizja drogowa",
            /* senseNumber */1
          ],
          /* :: */[
            /* record */[
              /* lemma */"bezkolizyjny",
              /* senseNumber */2
            ],
            /* :: */[
              /* record */[
                /* lemma */"katastrofa budowlana",
                /* senseNumber */1
              ],
              /* :: */[
                /* record */[
                  /* lemma */"wypadek drogowy",
                  /* senseNumber */1
                ],
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]
  ]
];

function loadRelations(send) {
  return Repromise.Rejectable[/* wait */6](send, Repromise.Rejectable[/* andThen */4]((function (param) {
                    var relations = param[1];
                    return Repromise.Rejectable[/* map */5]((function (synsetMap) {
                                  return /* RelationsLoaded */[
                                          relations,
                                          synsetMap
                                        ];
                                }), Repromise.Rejectable[/* map */5]((function (synsets) {
                                      return Belt_MapInt.fromArray(Belt_List.toArray(synsets));
                                    }), Repromise.Rejectable[/* all */8](Belt_List.map(param[0], (function (synsetId) {
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
                  }), Repromise.Rejectable[/* map */5]((function (param) {
                        return /* tuple */[
                                param[0],
                                Belt_Set.toList(Belt_Set.fromArray(Belt_List.toArray(Belt_List.flatten(param[1])), Domain$Wordnet.RelationCmp))
                              ];
                      }), Repromise.Rejectable[/* andThen */4]((function (synsetIds) {
                            return Repromise.Rejectable[/* map */5]((function (relations) {
                                          return /* tuple */[
                                                  synsetIds,
                                                  relations
                                                ];
                                        }), Repromise.Rejectable[/* all */8](Belt_List.map(Belt_SetInt.toList(Belt_SetInt.fromArray(Belt_List.toArray(synsetIds))), (function (synsetId) {
                                                  return Relations$Wordnet.network(synsetId, 2, /* () */0);
                                                }))));
                          }), Repromise.Rejectable[/* all */8](Belt_List.map(numberedSenses, (function (sense) {
                                    return Repromise.Rejectable[/* andThen */4]((function (sense) {
                                                  return Wordnet$Wordnet.synsetForSenseId(sense[/* id */0]);
                                                }), Repromise.Rejectable[/* map */5](Belt_List.headExn, Repromise.Rejectable[/* map */5]((function (senses) {
                                                          return Belt_List.keep(senses, (function (s) {
                                                                        if (s[/* lemma */1] === sense[/* lemma */0]) {
                                                                          return s[/* senseNumber */3] === sense[/* senseNumber */1];
                                                                        } else {
                                                                          return false;
                                                                        }
                                                                      }));
                                                        }), Wordnet$Wordnet.searchSenses(sense[/* lemma */0]))));
                                  })))))));
}

var component = ReasonReact.reducerComponent("Four-Wordnet");

function make(param) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return loadRelations(self[/* send */3]);
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var description = ReasonReact.element(undefined, undefined, TaskDescription$Wordnet.make(ReasonReact.element(undefined, undefined, MaterialUi_Typography.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */["Display as a directed graph semantic relations between the groups of lexemes."])), /* array */[]));
              var synsetIds = Belt_List.fromArray(Belt_MapInt.keysToArray(self[/* state */1][/* synsetMap */1]));
              var synsets = Belt_MapInt.valuesToArray(self[/* state */1][/* synsetMap */1]);
              var mainNodes = Belt_Array.map(synsets, (function (synset) {
                      return {
                              id: synset[/* synsetId */0],
                              label: Util$Wordnet.label(synset[/* synsetId */0], self[/* state */1][/* synsetMap */1]),
                              group: 1
                            };
                    }));
              var sideNodes = Belt_Array.map(Belt_List.toArray(Relations$Wordnet.closure(synsetIds, self[/* state */1][/* relations */0])), (function (synsetId) {
                      return {
                              id: synsetId,
                              label: Util$Wordnet.label(synsetId, self[/* state */1][/* synsetMap */1]),
                              group: 2
                            };
                    }));
              var nodes = Belt_Array.concat(mainNodes, sideNodes);
              var edges = Belt_List.toArray(Belt_List.map(self[/* state */1][/* relations */0], (function (relation) {
                          return {
                                  from: relation[/* relFrom */1],
                                  to: relation[/* relTo */2],
                                  label: relation[/* relationName */5]
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
                  length: 200,
                  shadow: true,
                  smooth: {
                    type: "dynamic"
                  }
                }
              };
              var graph = ReasonReact.element(undefined, undefined, Graph$Wordnet.make(nodes, edges, options, /* array */[]));
              return React.createElement("div", {
                          className: root
                        }, description, React.createElement("div", {
                              className: graphContainer
                            }, self[/* state */1][/* ready */2] ? graph : React.createElement("div", {
                                    className: progressContainer
                                  }, ReasonReact.element(undefined, undefined, MaterialUi_CircularProgress.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[])))));
            }),
          /* initialState */(function (param) {
              return initialState;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, param) {
              var relations = action[0];
              console.log("loaded");
              console.log(Belt_List.toArray(relations));
              return /* Update */Block.__(0, [/* record */[
                          /* relations */relations,
                          /* synsetMap */action[1],
                          /* ready */true
                        ]]);
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.initialState = initialState;
exports.numberedSenses = numberedSenses;
exports.loadRelations = loadRelations;
exports.component = component;
exports.make = make;
/* boldText Not a pure module */