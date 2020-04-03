import { createContext, useContext } from "react";

import FeedStore from "./Feed";
import UrlStore from "./Url";
import { VersionStore } from "./Version";

interface Store {
  urlStore: UrlStore;
  feedStore: FeedStore;
  versionStore: VersionStore;
}

export const store: Store = {
  urlStore: new UrlStore(),
  feedStore: new FeedStore(),
  versionStore: new VersionStore()
};

export const storeContext = createContext(store);

export function useStore() {
  return useContext(storeContext);
}
