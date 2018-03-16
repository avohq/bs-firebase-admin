type t;

module Error = {
  type t;
};

module Database = {
  type t;
  module rec Reference: {
    type t;
    [@bs.get] external key : t => Js.nullable(string) = "";
    [@bs.get] external parent : t => Js.nullable(t) = "";
    [@bs.get] external unsafeParent : t => t = "parent";
    [@bs.get] external root : t => t = "";
    [@bs.send] external child : (t, ~path: string) => t = "";
    [@bs.send.pipe: t]
    external once : (~eventType: string) => Js.Promise.t(DataSnapshot.t) = "";
    type cb = DataSnapshot.t => unit;
    [@bs.send.pipe: t]
    external on :
      (
        ~eventType: string,
        ~callback: DataSnapshot.t => unit,
        ~cancelCallback: Error.t => unit=?,
        unit
      ) =>
      cb =
      "";
    [@bs.send.pipe: t]
    external off :
      (~eventType: string, ~callback: DataSnapshot.t => unit=?, unit) => unit =
      "";
    [@bs.send.pipe: t] external set : (~value: 'a) => Js.Promise.t(unit) = "";
    [@bs.send.pipe: t]
    external update :
      (~value: 'a, ~onComplete: Js.undefined(Error.t) => unit=?, unit) =>
      Js.Promise.t(unit) =
      "";
    [@bs.send.pipe: t]
    external push :
      (
        ~value: Js.t('a)=?,
        ~onComplete: Js.undefined(Error.t) => unit=?,
        unit
      ) =>
      t =
      "";
  } = Reference
  and DataSnapshot: {
    type t;
    [@bs.get] external key : t => Js.nullable(string) = "";
    [@bs.get] external ref : t => Reference.t = "";
    [@bs.send] external child : (t, ~path: string) => t = "";
    [@bs.send] external exists : t => bool = "";
    [@bs.send] external exportVal : t => Js.Json.t = "exportVal";
    [@bs.send] external foreach : (t, t => bool) => bool = "forEach";
    [@bs.send] external hasChild : (t, ~path: string) => bool = "hasChild";
    [@bs.send] external hasChildren : t => bool = "hasChildren";
    [@bs.send] external numChildren : t => int = "numChildren";
    [@bs.send] external toJson : t => Js.Json.t = "toJSON";
    [@bs.send] external val_ : t => Js.Json.t = "val";
  } = DataSnapshot;
  module ThenableReference = {
    type t;
  };
  module Query = {
    type t;
  };
  [@bs.send.pipe: t] external ref : (~path: string=?) => Reference.t = "";
  [@bs.send]
  external refFromUrl : (t, ~url: string) => Reference.t = "refFromURL";
};

module Credential = {
  type t;
  [@bs.module "firebase-admin"] [@bs.scope "credential"]
  external cert : Js.t('a) => t = "cert";
};

module Auth = {
  type t;
  [@bs.send.pipe: t]
  external createCustomToken : (string, Js.t('a)) => Js.Promise.t(string) =
    "";
  [@bs.send.pipe: t]
  external verifyIdToken : string => Js.Promise.t(Js.t('a)) = "";
};

module App = {
  type t;
};

[@bs.send] external database : t => Database.t = "";

[@bs.send] external auth : t => Auth.t = "";

[@bs.module "firebase-admin"]
external initializeApp : (~options: Js.t('a)) => t = "initializeApp";
