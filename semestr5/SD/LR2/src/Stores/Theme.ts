import { makeAutoObservable } from "mobx";

type Theme = "light" | "dark";

export class ThemeStore {
  theme:Theme = "light";

  constructor() {
    makeAutoObservable(this);
  }

  setTheme(theme: Theme) {
    this.theme = theme;
  }
}
