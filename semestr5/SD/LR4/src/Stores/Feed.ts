import FeedModel from "@Models/Feed";
import UrlModel from "@Models/Url";
import feedService from "@Services/Feed";
import { makeAutoObservable, reaction, runInAction } from "mobx";
import { FeedItem } from "react-native-rss-parser";
import uuid from "react-native-uuid";

export default class FeedStore {
  url: UrlModel | null = null;
  feeds: FeedModel[] = [];

  constructor() {
    makeAutoObservable(this);
    reaction(
      () => this.url,
      () => {
        this.url === null && this.setFeeds([]);
      }
    );
  }

  setUrl(url: UrlModel | null) {
    this.url = url;
  }

  async setFeeds(feeds: FeedItem[]) {
    this.feeds = feeds.map((x) => {
      return {
        id: uuid.v4().toString(),
        title: x.title,
        link: x.links[0].url,
        date: new Date(x.published).toLocaleString("ru-Ru"),
        urlId: this.url!.id,
        image: x.enclosures.length ? x.enclosures[0].url : ""
      };
    });
    this.feeds.slice(0, 10).forEach(async (x) => await feedService.cashFeed(x, this.url!));
  }

  async getFeeds() {
    const feeds = await feedService.getFeeds(this.url!);
    runInAction(() => {
      this.feeds = feeds;
    });
  }
}
