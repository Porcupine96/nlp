// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Set = require("bs-platform/lib/js/belt_Set.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Repromise = require("@aantron/repromise/src/js/repromise.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_MapInt = require("bs-platform/lib/js/belt_MapInt.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Belt_SetInt = require("bs-platform/lib/js/belt_SetInt.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var LCH$Wordnet = require("../infrastructure/LCH.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Util$Wordnet = require("../infrastructure/Util.bs.js");
var Graph$Wordnet = require("../infrastructure/Graph.bs.js");
var Domain$Wordnet = require("../domain/Domain.bs.js");
var Wordnet$Wordnet = require("../infrastructure/Wordnet.bs.js");
var MaterialUi_Paper = require("@jsiebern/bs-material-ui/src/MaterialUi_Paper.bs.js");
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

var root = Css.style(/* :: */[
      Css.height(Css.pct(90)),
      /* [] */0
    ]);

var setPickerContainer = Css.style(/* :: */[
      Css.height(Css.rem(3)),
      /* :: */[
        Css.width(Css.pct(90)),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* [] */0
        ]
      ]
    ]);

var container = Css.style(/* :: */[
      Css.height(Css.rem(6)),
      /* :: */[
        Css.width(Css.pct(90)),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* [] */0
        ]
      ]
    ]);

var distanceBlock = Css.style(/* :: */[
      Css.height(Css.rem(6)),
      /* :: */[
        Css.width(Css.rem(16)),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* :: */[
            Css.alignItems(/* center */98248149),
            /* :: */[
              Css.marginLeft(Css.rem(0)),
              /* :: */[
                Css.marginRight(/* auto */-1065951377),
                /* :: */[
                  Css.paddingLeft(Css.rem(2)),
                  /* [] */0
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var setPicker = Css.style(/* :: */[
      Css.width(Css.rem(16)),
      /* :: */[
        Css.marginRight(Css.rem(0)),
        /* :: */[
          Css.marginLeft(/* auto */-1065951377),
          /* [] */0
        ]
      ]
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
  /* setPickerContainer */setPickerContainer,
  /* container */container,
  /* distanceBlock */distanceBlock,
  /* setPicker */setPicker,
  /* graphContainer */graphContainer,
  /* progressContainer */progressContainer
];

var initialState = /* record */[
  /* relations : [] */0,
  /* synsetIds : [] */0,
  /* synsetMap */Belt_MapInt.empty,
  /* leftIndex */0,
  /* rightIndex */1,
  /* distance */undefined,
  /* ready */false
];

var words = /* array */[
  /* record */[
    /* lemma */"szkoda",
    /* senseNumber */2
  ],
  /* record */[
    /* lemma */"wypadek",
    /* senseNumber */1
  ],
  /* record */[
    /* lemma */"kolizja",
    /* senseNumber */1
  ],
  /* record */[
    /* lemma */"kolizja",
    /* senseNumber */2
  ],
  /* record */[
    /* lemma */"nieszczęście",
    /* senseNumber */2
  ],
  /* record */[
    /* lemma */"katastrofa budowlana",
    /* senseNumber */1
  ]
];

function loadRelations(leftIndex, rightIndex, send) {
  return Repromise.Rejectable[/* wait */6](send, Repromise.Rejectable[/* andThen */4]((function (param) {
                    var relations = param[1];
                    var distinctSynsetIds = Belt_SetInt.toList(Belt_SetInt.fromArray(Belt_List.toArray(param[0])));
                    return Repromise.Rejectable[/* map */5]((function (synsetMap) {
                                  return /* RelationsLoaded */Block.__(0, [
                                            distinctSynsetIds,
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
                                                  return Relations$Wordnet.network(synsetId, 2, Caml_option.some(Belt_SetInt.fromArray(/* array */[
                                                                      10,
                                                                      11
                                                                    ])), /* () */0);
                                                }))));
                          }), Repromise.Rejectable[/* all */8](Belt_List.map(/* :: */[
                                  Belt_Array.getExn(words, leftIndex),
                                  /* :: */[
                                    Belt_Array.getExn(words, rightIndex),
                                    /* [] */0
                                  ]
                                ], (function (sense) {
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

var component = ReasonReact.reducerComponent("Five-Wordnet");

function make(param) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return loadRelations(self[/* state */1][/* leftIndex */3], self[/* state */1][/* rightIndex */4], self[/* send */3]);
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var description = ReasonReact.element(undefined, undefined, TaskDescription$Wordnet.make(ReasonReact.element(undefined, undefined, MaterialUi_Typography.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */["Display as a directed graph semantic relations between the groups of lexemes."])), /* array */[]));
              var match = self[/* state */1][/* distance */5];
              var distanceBlock$1 = ReasonReact.element(undefined, undefined, MaterialUi_Paper.make(distanceBlock, undefined, undefined, undefined, undefined, undefined, /* array */[ReasonReact.element(undefined, undefined, MaterialUi_Typography.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */["Leacock Chodorow: " + (
                                    match !== undefined ? (function (param) {
                                            return param.toFixed(5);
                                          })(match) : "?"
                                  )]))]));
              var chooseWord = function (index, onChange) {
                return React.createElement("div", {
                            className: setPickerContainer
                          }, ReasonReact.element(undefined, undefined, MaterialUi_Select.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, (function (param, update) {
                                      return Curry._1(onChange, update.props.value);
                                    }), undefined, undefined, undefined, undefined, undefined, /* `Int */[
                                    3654863,
                                    index
                                  ], undefined, undefined, undefined, setPicker, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[Belt_Array.map(Belt_Array.zip(words, Belt_Array.range(0, words.length)), (function (param) {
                                            var word = param[0];
                                            return ReasonReact.element(undefined, undefined, MaterialUi_MenuItem.make(undefined, undefined, undefined, undefined, undefined, /* `Int */[
                                                            3654863,
                                                            param[1]
                                                          ], undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[word[/* lemma */0] + (" (" + (String(word[/* senseNumber */1]) + ")"))]));
                                          }))])));
              };
              var mainNodes = Belt_Array.map(Belt_List.toArray(self[/* state */1][/* synsetIds */1]), (function (synsetId) {
                      return {
                              id: synsetId,
                              label: Util$Wordnet.label(synsetId, self[/* state */1][/* synsetMap */2]),
                              group: 1
                            };
                    }));
              var sideNodes = Belt_Array.map(Belt_List.toArray(Relations$Wordnet.closure(self[/* state */1][/* synsetIds */1], self[/* state */1][/* relations */0])), (function (synsetId) {
                      return {
                              id: synsetId,
                              label: Util$Wordnet.label(synsetId, self[/* state */1][/* synsetMap */2]),
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
                              className: container
                            }, distanceBlock$1, React.createElement("div", undefined, chooseWord(self[/* state */1][/* leftIndex */3], (function (wordIndex) {
                                        return Curry._1(self[/* send */3], /* LeftWordChosen */Block.__(1, [wordIndex]));
                                      })), chooseWord(self[/* state */1][/* rightIndex */4], (function (wordIndex) {
                                        return Curry._1(self[/* send */3], /* RightWordChosen */Block.__(2, [wordIndex]));
                                      })))), React.createElement("div", {
                              className: graphContainer
                            }, self[/* state */1][/* ready */6] ? graph : React.createElement("div", {
                                    className: progressContainer
                                  }, ReasonReact.element(undefined, undefined, MaterialUi_CircularProgress.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[])))));
            }),
          /* initialState */(function (param) {
              return initialState;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              switch (action.tag | 0) {
                case 0 : 
                    var relations = action[1];
                    var synsetIds = action[0];
                    var distance = Belt_Option.map(Relations$Wordnet.shortestPathLength(synsetIds, relations), (function (shortestPath) {
                            return LCH$Wordnet.calculate(shortestPath, undefined, /* () */0);
                          }));
                    return /* Update */Block.__(0, [/* record */[
                                /* relations */relations,
                                /* synsetIds */synsetIds,
                                /* synsetMap */action[2],
                                /* leftIndex */state[/* leftIndex */3],
                                /* rightIndex */state[/* rightIndex */4],
                                /* distance */distance,
                                /* ready */true
                              ]]);
                case 1 : 
                    var leftIndex = action[0];
                    return /* UpdateWithSideEffects */Block.__(2, [
                              /* record */[
                                /* relations */state[/* relations */0],
                                /* synsetIds */state[/* synsetIds */1],
                                /* synsetMap */state[/* synsetMap */2],
                                /* leftIndex */leftIndex,
                                /* rightIndex */state[/* rightIndex */4],
                                /* distance */state[/* distance */5],
                                /* ready */false
                              ],
                              (function (self) {
                                  return loadRelations(leftIndex, self[/* state */1][/* rightIndex */4], self[/* send */3]);
                                })
                            ]);
                case 2 : 
                    var rightIndex = action[0];
                    return /* UpdateWithSideEffects */Block.__(2, [
                              /* record */[
                                /* relations */state[/* relations */0],
                                /* synsetIds */state[/* synsetIds */1],
                                /* synsetMap */state[/* synsetMap */2],
                                /* leftIndex */state[/* leftIndex */3],
                                /* rightIndex */rightIndex,
                                /* distance */state[/* distance */5],
                                /* ready */false
                              ],
                              (function (self) {
                                  return loadRelations(self[/* state */1][/* leftIndex */3], rightIndex, self[/* send */3]);
                                })
                            ]);
                
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.initialState = initialState;
exports.words = words;
exports.loadRelations = loadRelations;
exports.component = component;
exports.make = make;
/* boldText Not a pure module */
