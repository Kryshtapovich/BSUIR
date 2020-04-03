import { makeAutoObservable } from "mobx";

enum Scale {
  small = 0.8,
  normal = 1,
  huge = 1.2
}

export class FontStore {
  scale: Scale = 1;

  constructor() {
    makeAutoObservable(this);
  }

  setScale(scale: Scale) {
    this.scale = scale;
  }
}
