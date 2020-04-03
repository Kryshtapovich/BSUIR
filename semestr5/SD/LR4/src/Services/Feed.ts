import * as Sqlite from "expo-sqlite";

import UrlModel from "@Models/Url";
import FeedModel from "@Models/Feed";

class FeedService {
  constructor() {
    const db = Sqlite.openDatabase("RssReader");
    db.transaction((t) =>
      t.executeSql(
        "create table if not exists Feed (" +
          "id nvarchar(40) primary key not null," +
          "title nvarchar(1000)," +
          "link nvarchar(1000)," +
          "date nvarchar(20)," +
          "urlId nvarchar(40)," +
          "image nvarchar(1000))"
      )
    );
  }

  cashFeed(feed: FeedModel, url: UrlModel) {
    const db = Sqlite.openDatabase("RssReader");
    return new Promise<void>(() => {
      db.transaction((t) => t.executeSql("delete from Feed where urlId=?", [url.id]));
      db.transaction((t) =>
        t.executeSql(
          "insert into Feed (id, title, link, date, urlId, image) values (?, ?, ?, ?, ?, ?)",
          [feed.id, feed.title, feed.link, feed.date, url.id, feed.image]
        )
      );
    });
  }

  getFeeds(url: UrlModel) {
    const db = Sqlite.openDatabase("RssReader");
    return new Promise<FeedModel[]>((resolve) => {
      db.transaction((t) =>
        t.executeSql("select * from Feed where urlId=?", [url.id], (_, { rows }) => {
          resolve((rows as any)._array as FeedModel[]);
          return rows;
        })
      );
    });
  }
}

const feedService = new FeedService();

export default feedService;
