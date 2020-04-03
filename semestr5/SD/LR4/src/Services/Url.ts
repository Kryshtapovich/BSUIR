import * as Sqlite from "expo-sqlite";

import UrlModel from "@Models/Url";

class UrlService {
  constructor() {
    const db = Sqlite.openDatabase("RssReader");
    db.transaction((t) =>
      t.executeSql(
        "create table if not exists Url (" +
          "id nvarchar(40) primary key not null," +
          "url nvarchar(2048))"
      )
    );
  }

  getUrls() {
    const db = Sqlite.openDatabase("RssReader");
    return new Promise<UrlModel[]>((resolve) =>
      db.transaction((t) =>
        t.executeSql("select id, url from Url", [], (_, { rows }) => {
          resolve((rows as any)._array as UrlModel[]);
          return rows;
        })
      )
    );
  }

  addUrl(url: UrlModel) {
    const db = Sqlite.openDatabase("RssReader");
    return new Promise<void>(() =>
      db.transaction((t) =>
        t.executeSql("insert into Url (id, url) values (?, ?)", [url.id, url.url])
      )
    );
  }

  deleteUrl(id: string) {
    const db = Sqlite.openDatabase("RssReader");
    return new Promise<void>(() => {
      db.transaction((t) => t.executeSql("delete from Url where id=?", [id]));
      db.transaction((t) => t.executeSql("delete from Feed where urlId=?", [id]));
    });
  }
}

const urlService = new UrlService();

export default urlService;
