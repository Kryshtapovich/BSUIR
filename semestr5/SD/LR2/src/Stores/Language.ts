import { makeAutoObservable } from "mobx";

type Language = "ru" | "en";

export class LanguageStore {
  language: Language = "en";

  constructor() {
    makeAutoObservable(this);
  }

  setLanguage(language: Language) {
    this.language = language;
  }
}
