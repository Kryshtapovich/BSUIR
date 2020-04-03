import { makeAutoObservable, runInAction } from "mobx";

export class VersionStore {
  version: string = "";

  constructor() {
    makeAutoObservable(this);
  }

  init = async () => {
    const tags = await fetch("https://api.github.com/repos/Krishtapovich/Calculator/tags").then(
      (respone) => respone.json()
    );
    runInAction(() => {
      this.version = tags[0].name;
    });
  };
}
