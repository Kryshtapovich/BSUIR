import UrlModel from "@Models/Url";
import urlService from "@Services/Url";
import { makeAutoObservable, runInAction } from "mobx";
import uuid from "react-native-uuid";

export default class UrlStore {
  urls: UrlModel[] = [];

  constructor() {
    makeAutoObservable(this);
  }

  async init() {
    const urls = await urlService.getUrls();
    runInAction(() => (this.urls = urls));
  }

  async addUrl(url: string) {
    const newUrl = { id: uuid.v4().toString(), url };
    this.urls.push(newUrl);
    await urlService.addUrl(newUrl);
  }

  async deleteUrl(url: UrlModel) {
    this.urls = this.urls.filter((x) => x.id !== url.id);
    await urlService.deleteUrl(url.id);
  }
}
