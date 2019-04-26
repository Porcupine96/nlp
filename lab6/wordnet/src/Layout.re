open MaterialUi;

module Styles = {
  open Css;

  let layout =
    style([display(`flex), height(pct(100.)), width(pct(100.))]);

  let graphic = style([width(px(50)), height(px(50))]);

  let drawerWidth = 270;

  let drawer = style([width(drawerWidth->px), flexShrink(0)]);

  let drawerPaper = style([width(drawerWidth->px)]);

  let page = style([flexGrow(1.0), padding(32->px), marginTop(64->px)]);

  let drawerHeader =
    style([
      display(`flex),
      flexDirection(`column),
      height(px(100)),
      width(pct(100.)),
      justifyContent(`center),
      alignItems(`center),
      marginTop(px(18)),
    ]);

  let headerIcon = style([fontSize(px(32))]);

  let title = style([fontSize(px(18))]);
};

let graphicUrl = "https://emojipedia-us.s3.dualstack.us-west-1.amazonaws.com/thumbs/160/apple/198/robot-face_1f916.png";

let component = ReasonReact.statelessComponent(__MODULE__);

let make = children => {
  ...component,
  render: _ =>
    <div className=Styles.layout>
      <Drawer
        variant=`Permanent
        open_=true
        className=Styles.drawer
        classes=[Paper(Styles.drawerPaper)]>
        <div className=Styles.drawerHeader>
          <img src=graphicUrl className=Styles.graphic />
          <p className=Styles.title>
            {ReasonReact.string("NLP - assignment 6")}
          </p>
        </div>
        <Divider />
        <List>
          <ListItem key="1" button=true>
            <ListItemIcon>
              <MscharleyBsMaterialUiIcons.LooksOne.Outlined />
            </ListItemIcon>
            <ListItemText
              primary={ReasonReact.string("\"szkoda\" synonyms")}
            />
          </ListItem>
          <ListItem key="2" button=true>
            <ListItemIcon>
              <MscharleyBsMaterialUiIcons.LooksTwo.Outlined />
            </ListItemIcon>
            <ListItemText
              primary={ReasonReact.string("\"wypadek drogowy\" hypernyms")}
            />
          </ListItem>
          <ListItem key="3" button=true>
            <ListItemIcon>
              <MscharleyBsMaterialUiIcons.Looks3.Outlined />
            </ListItemIcon>
            <ListItemText
              primary={ReasonReact.string("\"wypadek drogowy\" closures")}
            />
          </ListItem>
          <ListItem key="4" button=true>
            <ListItemIcon>
              <MscharleyBsMaterialUiIcons.Looks4.Outlined />
            </ListItemIcon>
            <ListItemText
              primary={ReasonReact.string("\"wypadek\" direct hyponyms")}
            />
          </ListItem>
          <ListItem key="5" button=true>
            <ListItemIcon>
              <MscharleyBsMaterialUiIcons.Looks5.Outlined />
            </ListItemIcon>
            <ListItemText
              primary={ReasonReact.string("\"wypadek\" 2nd order hyponyms")}
            />
          </ListItem>
          <ListItem key="6" button=true>
            <ListItemIcon>
              <MscharleyBsMaterialUiIcons.Looks6.Outlined />
            </ListItemIcon>
            <ListItemText
              primary={ReasonReact.string("Leacock-Chodorow similarity")}
            />
          </ListItem>
        </List>
        <Divider />
      </Drawer>
      <div className=Styles.page> {children |> ReasonReact.array} </div>
    </div>,
};
