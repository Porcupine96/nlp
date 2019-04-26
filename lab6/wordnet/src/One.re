open Belt;
open Repromise.Rejectable;

module Styles = {
  open Css;

  let boldText = style([fontWeight(`bold)]);

  let table = style([width(pct(90.))]);
};

type synsetId = string;

type synset = {
  synsetId: int,
  senses: list(Wordnet.sense),
};

type action =
  | SynsetsLoaded(list(synset));

type state = {synsets: list(synset)};

let loadSynsets = (send: action => unit) =>
  Wordnet.searchSenses("szkoda")
  |> andThen(senses =>
       Repromise.Rejectable.all(
         List.map(senses, (sense: Wordnet.sense) =>
           Wordnet.synsetForSenseId(sense.id)
         ),
       )
     )
  |> andThen(synsetIds =>
       Repromise.Rejectable.all(
         synsetIds
         ->List.map(synsetId =>
             Wordnet.sensesForSynset(synsetId)
             |> map(senses => {synsetId, senses})
           ),
       )
     )
  |> map(synsets => SynsetsLoaded(synsets))
  |> wait(send);

let initialState = {synsets: []};

let component = ReasonReact.reducerComponent(__MODULE__);

/* let headCells = (synsets: array(Wordnet.synset)) => */
/*   synsets */
/*   ->Array.map(synset => */
/*       <TableCell key={string_of_int(synset##synsetId)}> */
/*         {ReasonReact.string(synset##baseLemma)} */
/*         {ReasonReact.string(" ")} */
/*         {ReasonReact.string("(" ++ string_of_int(synset##synsetId) ++ ")")} */
/*       </TableCell> */
/*     ); */

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: self => loadSynsets(self.send),
  reducer: (action, state: state) =>
    switch (action) {
    | SynsetsLoaded(synsets) =>
      Js.log(synsets);
      ReasonReact.NoUpdate;
    },
  render: _ =>
    <div>
      <TaskDescription>
        <M.Typography>
          {ReasonReact.string("Find all meaning of the szkoda ")}
          {ReasonReact.string(" noun ")}
          {ReasonReact.string("and display all their synonyms.")}
        </M.Typography>
      </TaskDescription>
      <M.Paper className=Styles.table>
        <M.Table className=Styles.table>
          <M.TableHead>
            <M.TableRow
              /* {ReasonReact.array(headCells(self.state.synsets))} */
            />
          </M.TableHead>
        </M.Table>
      </M.Paper>
    </div>,
};
