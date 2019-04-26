// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Link$Wordnet = require("./Link.bs.js");
var MaterialUi_List = require("@jsiebern/bs-material-ui/src/MaterialUi_List.bs.js");
var MaterialUi_Drawer = require("@jsiebern/bs-material-ui/src/MaterialUi_Drawer.bs.js");
var MaterialUi_Divider = require("@jsiebern/bs-material-ui/src/MaterialUi_Divider.bs.js");
var MaterialUi_ListItem = require("@jsiebern/bs-material-ui/src/MaterialUi_ListItem.bs.js");
var MaterialUi_ListItemIcon = require("@jsiebern/bs-material-ui/src/MaterialUi_ListItemIcon.bs.js");
var MaterialUi_ListItemText = require("@jsiebern/bs-material-ui/src/MaterialUi_ListItemText.bs.js");
var Looks3$MscharleyBsMaterialUiIcons = require("@mscharley/bs-material-ui-icons/src/icons/Looks3.bs.js");
var Looks4$MscharleyBsMaterialUiIcons = require("@mscharley/bs-material-ui-icons/src/icons/Looks4.bs.js");
var Looks5$MscharleyBsMaterialUiIcons = require("@mscharley/bs-material-ui-icons/src/icons/Looks5.bs.js");
var Looks6$MscharleyBsMaterialUiIcons = require("@mscharley/bs-material-ui-icons/src/icons/Looks6.bs.js");
var LooksOne$MscharleyBsMaterialUiIcons = require("@mscharley/bs-material-ui-icons/src/icons/LooksOne.bs.js");
var LooksTwo$MscharleyBsMaterialUiIcons = require("@mscharley/bs-material-ui-icons/src/icons/LooksTwo.bs.js");

var layout = Css.style(/* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.height(Css.pct(100)),
        /* :: */[
          Css.width(Css.pct(100)),
          /* [] */0
        ]
      ]
    ]);

var graphic = Css.style(/* :: */[
      Css.width(Css.px(50)),
      /* :: */[
        Css.height(Css.px(50)),
        /* [] */0
      ]
    ]);

var drawer = Css.style(/* :: */[
      Css.width(Css.px(270)),
      /* :: */[
        Css.flexShrink(0),
        /* [] */0
      ]
    ]);

var drawerPaper = Css.style(/* :: */[
      Css.width(Css.px(270)),
      /* [] */0
    ]);

var page = Css.style(/* :: */[
      Css.flexGrow(1.0),
      /* :: */[
        Css.padding(Css.px(32)),
        /* :: */[
          Css.marginTop(Css.px(64)),
          /* [] */0
        ]
      ]
    ]);

var drawerHeader = Css.style(/* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.flexDirection(/* column */-963948842),
        /* :: */[
          Css.height(Css.px(100)),
          /* :: */[
            Css.width(Css.pct(100)),
            /* :: */[
              Css.justifyContent(/* center */98248149),
              /* :: */[
                Css.alignItems(/* center */98248149),
                /* :: */[
                  Css.marginTop(Css.px(18)),
                  /* :: */[
                    Css.marginBottom(Css.px(8)),
                    /* [] */0
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var headerIcon = Css.style(/* :: */[
      Css.fontSize(Css.px(32)),
      /* [] */0
    ]);

var title = Css.style(/* :: */[
      Css.fontSize(Css.px(18)),
      /* [] */0
    ]);

var Styles = /* module */[
  /* layout */layout,
  /* graphic */graphic,
  /* drawerWidth */270,
  /* drawer */drawer,
  /* drawerPaper */drawerPaper,
  /* page */page,
  /* drawerHeader */drawerHeader,
  /* headerIcon */headerIcon,
  /* title */title
];

var graphicUrl = "https://emojipedia-us.s3.dualstack.us-west-1.amazonaws.com/thumbs/160/apple/198/robot-face_1f916.png";

var component = ReasonReact.statelessComponent("Layout-Wordnet");

var menuItems = /* array */[
  /* One */0,
  /* Two */1,
  /* Three */2,
  /* Four */3,
  /* Five */4,
  /* Six */5
];

function toMessage(item) {
  switch (item) {
    case 0 : 
        return "\"szkoda\" synonyms";
    case 1 : 
        return "\"wypadek drogowy\" hypernyms";
    case 2 : 
        return "\"wypadek drogowy\" closures";
    case 3 : 
        return "\"wypadek\" direct hyponyms";
    case 4 : 
        return "\"wypadek\" 2nd order hyponyms";
    case 5 : 
        return "Leacock-Chodorow similarity";
    
  }
}

function toIcon(item) {
  switch (item) {
    case 0 : 
        return ReasonReact.element(undefined, undefined, Curry._8(LooksOne$MscharleyBsMaterialUiIcons.Outlined[/* make */1], undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]));
    case 1 : 
        return ReasonReact.element(undefined, undefined, Curry._8(LooksTwo$MscharleyBsMaterialUiIcons.Outlined[/* make */1], undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]));
    case 2 : 
        return ReasonReact.element(undefined, undefined, Curry._8(Looks3$MscharleyBsMaterialUiIcons.Outlined[/* make */1], undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]));
    case 3 : 
        return ReasonReact.element(undefined, undefined, Curry._8(Looks4$MscharleyBsMaterialUiIcons.Outlined[/* make */1], undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]));
    case 4 : 
        return ReasonReact.element(undefined, undefined, Curry._8(Looks5$MscharleyBsMaterialUiIcons.Outlined[/* make */1], undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]));
    case 5 : 
        return ReasonReact.element(undefined, undefined, Curry._8(Looks6$MscharleyBsMaterialUiIcons.Outlined[/* make */1], undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]));
    
  }
}

function make(children) {
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
              var header = React.createElement("div", {
                    className: drawerHeader
                  }, React.createElement("img", {
                        className: graphic,
                        src: graphicUrl
                      }), React.createElement("p", {
                        className: title
                      }, "NLP - assignment 6"));
              var menu = Belt_Array.map(menuItems, (function (item) {
                      var icon = toIcon(item);
                      var message = toMessage(item);
                      return ReasonReact.element(undefined, undefined, Link$Wordnet.make(item, undefined, /* array */[ReasonReact.element(message, undefined, MaterialUi_ListItem.make(undefined, true, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[
                                                ReasonReact.element(undefined, undefined, MaterialUi_ListItemIcon.make(undefined, undefined, undefined, /* array */[icon])),
                                                ReasonReact.element(undefined, undefined, MaterialUi_ListItemText.make(undefined, undefined, undefined, Caml_option.some(message), undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]))
                                              ]))]));
                    }));
              return React.createElement("div", {
                          className: layout
                        }, ReasonReact.element(undefined, undefined, MaterialUi_Drawer.make(undefined, undefined, drawer, undefined, undefined, undefined, true, undefined, undefined, undefined, undefined, /* Permanent */950914574, /* :: */[
                                  /* Paper */Block.__(2, [drawerPaper]),
                                  /* [] */0
                                ], undefined, /* array */[
                                  header,
                                  ReasonReact.element(undefined, undefined, MaterialUi_Divider.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[])),
                                  ReasonReact.element(undefined, undefined, MaterialUi_List.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[menu])),
                                  ReasonReact.element(undefined, undefined, MaterialUi_Divider.make(undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* array */[]))
                                ])), React.createElement("div", {
                              className: page
                            }, children));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.graphicUrl = graphicUrl;
exports.component = component;
exports.menuItems = menuItems;
exports.toMessage = toMessage;
exports.toIcon = toIcon;
exports.make = make;
/* layout Not a pure module */
