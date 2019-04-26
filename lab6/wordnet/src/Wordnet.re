[%raw "require('isomorphic-fetch')"];

open Repromise.Rejectable;

type jsRepromise('a) = Repromise.Rejectable.t('a, Js.Promise.error);

type lexem = {
  .
  "senseId": string,
  "partOfSpeech": string,
};

let apiUrl = "http://api.slowosiec.clarin-pl.eu/plwordnet-api";

type senseSearchResponse = {senses: list(Domain.sense)};

let senseDecoder: Json.Decode.decoder(Domain.sense) =
  json =>
    Json.Decode.{
      id: json |> field("id", int),
      partOfSpeech:
        (
          json
          |> field("partOfSpeech", json =>
               {"lmfType": json |> field("lmfType", string)}
             )
        )##lmfType,
      lemma:
        (
          json
          |> field("lemma", json => {"word": json |> field("word", string)})
        )##word,
    };

let synsetDecoder: Json.Decode.decoder(Domain.synsetId) =
  json => json |> Json.Decode.field("id", Json.Decode.int);

let searchSenses: string => jsRepromise(list(Domain.sense)) = {
  let decode: Json.Decode.decoder(senseSearchResponse) =
    json =>
      Json.Decode.{senses: json |> field("content", list(senseDecoder))};

  word =>
    Js.Promise.(
      Fetch.fetch(apiUrl ++ "/senses/search?lemma=" ++ word)
      |> then_(Fetch.Response.json)
      |> then_(json => json |> decode |> resolve)
      |> fromJsPromise
      |> map(res => res.senses)
    );
};

let synsetForSenseId: int => jsRepromise(Domain.synsetId) =
  senseId =>
    Js.Promise.(
      Fetch.fetch(
        apiUrl ++ "/senses/" ++ string_of_int(senseId) ++ "/synset",
      )
      |> then_(Fetch.Response.json)
      |> then_(json => json |> synsetDecoder |> resolve)
      |> fromJsPromise
    );

let sensesForSynset: int => jsRepromise(list(Domain.sense)) = {
  let decode = Json.Decode.list(senseDecoder);

  synsetId =>
    Js.Promise.(
      Fetch.fetch(
        apiUrl ++ "/synsets/" ++ string_of_int(synsetId) ++ "/senses",
      )
      |> then_(Fetch.Response.json)
      |> then_(json => json |> decode |> resolve)
      |> fromJsPromise
    );
};
