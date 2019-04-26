open Belt;
open Router;

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
      marginBottom(px(8)),
    ]);

  let headerIcon = style([fontSize(px(32))]);

  let title = style([fontSize(px(18))]);
};

let graphicUrl = "https://emojipedia-us.s3.dualstack.us-west-1.amazonaws.com/thumbs/160/apple/198/robot-face_1f916.png";

let component = ReasonReact.statelessComponent(__MODULE__);

let menuItems: array(Router.route) = [|One, Two, Three, Four, Five, Six|];

let toMessage = item =>
  switch (item) {
  | One => "\"szkoda\" synonyms"
  | Two => "\"wypadek drogowy\" hypernyms"
  | Three => "\"wypadek drogowy\" closures"
  | Four => "\"wypadek\" direct hyponyms"
  | Five => "\"wypadek\" 2nd order hyponyms"
  | Six => "Leacock-Chodorow similarity"
  };

let toIcon = item =>
  switch (item) {
  | One => <MscharleyBsMaterialUiIcons.LooksOne.Outlined />
  | Two => <MscharleyBsMaterialUiIcons.LooksTwo.Outlined />
  | Three => <MscharleyBsMaterialUiIcons.Looks3.Outlined />
  | Four => <MscharleyBsMaterialUiIcons.Looks4.Outlined />
  | Five => <MscharleyBsMaterialUiIcons.Looks5.Outlined />
  | Six => <MscharleyBsMaterialUiIcons.Looks6.Outlined />
  };

let make = children => {
  ...component,
  render: _ => {
    let header =
      <div className=Styles.drawerHeader>
        <img src=graphicUrl className=Styles.graphic />
        <p className=Styles.title>
          {ReasonReact.string("NLP - assignment 6")}
        </p>
      </div>;

    let menu =
      menuItems
      ->Array.map(item => {
          let icon = toIcon(item);
          let message = toMessage(item);

          <Link route=item>
            <M.ListItem key=message button=true>
              <M.ListItemIcon> icon </M.ListItemIcon>
              <M.ListItemText primary={ReasonReact.string(message)} />
            </M.ListItem>
          </Link>;
        })
      ->ReasonReact.array;

    <div className=Styles.layout>
      <M.Drawer
        variant=`Permanent
        open_=true
        className=Styles.drawer
        classes=[Paper(Styles.drawerPaper)]>
        header
        <M.Divider />
        <M.List> menu </M.List>
        <M.Divider />
      </M.Drawer>
      <div className=Styles.page> {children |> ReasonReact.array} </div>
    </div>;
  },
};
