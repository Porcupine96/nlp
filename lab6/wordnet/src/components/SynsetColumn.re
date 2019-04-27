open Belt;

module Styles = {
  open Css;

  let root =
    style([width(pct(33.)), marginLeft(px(10)), marginRight(px(10))]);
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~synset: Domain.synset, _) => {
  ...component,
  render: _ => {
    let header =
      <M.TableRow>
        <M.TableCell>
          {ReasonReact.string("synset: " ++ string_of_int(synset.synsetId))}
        </M.TableCell>
      </M.TableRow>;

    let rows =
      synset.senses
      ->List.toArray
      ->Array.map(sense =>
          <M.TableRow key={string_of_int(sense.id)}>
            <M.TableCell>
              {
                ReasonReact.string(
                  sense.lemma ++ " (" ++ sense.partOfSpeech ++ ")",
                )
              }
            </M.TableCell>
          </M.TableRow>
        )
      ->ReasonReact.array;

    <M.Paper className=Styles.root>
      <M.Table>
        <M.TableHead> header </M.TableHead>
        <M.TableBody> rows </M.TableBody>
      </M.Table>
    </M.Paper>;
  },
};
