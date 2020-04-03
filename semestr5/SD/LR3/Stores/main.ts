import { createContext, useContext } from "react";
import { NoteStore } from "./Note";

import { VersionStore } from "./Version";

interface Store {
  noteStore: NoteStore;
  versionStore: VersionStore;
}

export const store: Store = {
  noteStore: new NoteStore(),
  versionStore: new VersionStore()
};

export const StoreContext = createContext(store);

export function useStore() {
  return useContext(StoreContext);
}
