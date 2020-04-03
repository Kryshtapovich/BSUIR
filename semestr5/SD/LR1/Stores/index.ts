import { createContext, useContext } from "react";

import CalculatorStore from "./Calculator";
import ThemeStore from "./Theme";
import { VersionStore } from "./Version";

interface Store {
  calculatorStore: CalculatorStore;
  versionStore: VersionStore;
  themeStore: ThemeStore;
}

export const store: Store = {
  calculatorStore: new CalculatorStore(),
  themeStore: new ThemeStore(),
  versionStore: new VersionStore()
};

export const StoreContext = createContext(store);

export function useStore() {
  return useContext(StoreContext);
}
