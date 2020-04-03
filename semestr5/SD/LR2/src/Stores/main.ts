import { createContext, useContext } from "react";
import { FontStore } from "./Font";
import { LanguageStore } from "./Language";

import { SessionStore } from "./Session";
import { ThemeStore } from "./Theme";
import { TimerStore } from "./Timer";
import { VersionStore } from "./Version";

interface Store {
  timerStore: TimerStore;
  sessionStore: SessionStore;
  versionStore: VersionStore;
  themeStore: ThemeStore;
  fontStore: FontStore;
  languageStore: LanguageStore;
}

export const store: Store = {
  timerStore: new TimerStore(),
  sessionStore: new SessionStore(),
  versionStore: new VersionStore(),
  themeStore: new ThemeStore(),
  fontStore: new FontStore(),
  languageStore: new LanguageStore()
};

export const storeContext = createContext(store);

export function useStore() {
  return useContext(storeContext);
}
