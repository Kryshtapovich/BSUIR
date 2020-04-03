import { makeAutoObservable } from "mobx";

import { darkTheme, lightTheme } from "../Assets/Themes";

export default class ThemeStore {
  isLight: boolean = true;

  constructor() {
    makeAutoObservable(this);
  }

  toggle = () => {
    this.isLight = !this.isLight;
  };

  get activeTheme() {
    return this.isLight ? lightTheme : darkTheme;
  }
}
