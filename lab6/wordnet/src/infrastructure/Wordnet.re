[%raw "require('isomorphic-fetch')"];

open Promise.Js;

type jsPromise('a) = Promise.Js.t('a, Js.Promise.error);

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
      partOfSpeech: (json |> field("partOfSpeech", json => {"lmfType": json |> field("lmfType", string)}))##lmfType,
      lemma: (json |> field("lemma", json => {"word": json |> field("word", string)}))##word,
      senseNumber: json |> field("senseNumber", int),
    };

let synsetDecoder: Json.Decode.decoder(int) = json => json |> Json.Decode.field("id", Json.Decode.int);

let relationIdToKind: int => Domain.relationKind =
  relationId =>
    switch (relationId) {
    | 10 => Domain.Hyponym
    | 11 => Domain.Hypernymy
    | _ => Domain.Other
    };

let relationDecoder: Json.Decode.decoder(Domain.relation) =
  json =>
    Json.Decode.{
      id: json |> field("id", int),
      relFrom: (json |> field("synsetFrom", json => {"id": json |> field("id", int)}))##id,
      relTo: (json |> field("synsetTo", json => {"id": json |> field("id", int)}))##id,
      relationKind: relationIdToKind(json |> field("relation", json => json |> field("id", int))),
      relationId: json |> field("relation", json => json |> field("id", int)),
      relationName: json |> field("relation", json => json |> field("name", string)),
    };

let searchSenses: string => jsPromise(list(Domain.sense)) = {
  let decode: Json.Decode.decoder(senseSearchResponse) = json => Json.Decode.{senses: json |> field("content", list(senseDecoder))};

  word => {
    Js.Promise.(
      Fetch.fetch(apiUrl ++ "/senses/search?lemma=" ++ word)
      |> then_(Fetch.Response.json)
      |> then_(json => json |> decode |> resolve)
      // |> then_(json => {
      //      Js.log(word);
      //      Js.log(json);
      //      json |> decode |> resolve;
      //    })
    )
    ->fromBsPromise
    ->map(res => res.senses)
  };
};

let synsetForSenseId: int => jsPromise(int) =
  senseId =>
    Js.Promise.(
      Fetch.fetch(apiUrl ++ "/senses/" ++ string_of_int(senseId) ++ "/synset")
      |> then_(Fetch.Response.json)
      |> then_(json => json |> synsetDecoder |> resolve)
      |> fromBsPromise
    );

let sensesForSynset: int => jsPromise(list(Domain.sense)) = {
  let decode = Json.Decode.list(senseDecoder);

  synsetId =>
    Js.Promise.(
      Fetch.fetch(apiUrl ++ "/synsets/" ++ string_of_int(synsetId) ++ "/senses")
      |> then_(Fetch.Response.json)
      |> then_(json => json |> decode |> resolve)
      |> fromBsPromise
    );
};

let relationsForSynset: int => jsPromise(list(Domain.relation)) = {
  let decode = Json.Decode.list(relationDecoder);

  synsetId =>
    Js.Promise.(
      Fetch.fetch(apiUrl ++ "/synsets/" ++ string_of_int(synsetId) ++ "/relations")
      |> then_(Fetch.Response.json)
      |> then_(json => json |> decode |> resolve)
      // |> then_(json => {
      //      Js.log(json);
      //      json |> decode |> resolve;
      //    })
      |> fromBsPromise
    );
};