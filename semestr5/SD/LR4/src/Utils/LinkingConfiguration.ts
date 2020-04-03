import { LinkingOptions } from "@react-navigation/native";
import * as Linking from "expo-linking";

import { RootStackParamList } from "./Types";

const linking: LinkingOptions<RootStackParamList> = {
  prefixes: [Linking.makeUrl("/")],
  config: {
    screens: {
      Root: {
        screens: {
          Feeds: {
            screens: {
              FeedsScreen: "one"
            }
          },
          Urls: {
            screens: {
              UrlsScreen: "two"
            }
          }
        }
      }
    }
  }
};

export default linking;
