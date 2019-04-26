/* open Belt; */
/* open Repromise.Rejectable; */
/* let getSenses = (lexems: array(Wordnet.lexem)) => */
/*   Repromise.Rejectable.all( */
/*     List.fromArray(lexems) */
/*     /\* ->List.keep(lexem => lexem##partOfSpeech == "noun_pl") *\/ */
/*     ->List.map(lexem => Wordnet.senses(lexem##senseId) |> fromJsPromise), */
/*   ) */
/*   |> catch(error => { */
/*        Js.log(error); */
/*        rejected(error); */
/*      }); */
/* Wordnet.lexemes("szkoda") */
/* |> fromJsPromise */
/* |> andThen(getSenses) */
/* |> wait(responses => responses->List.forEach(res => Js.log(res##synset))); */
