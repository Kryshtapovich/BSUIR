import FeedModel from "@Models/Feed";
import { StyleSheet } from "react-native";

const defaultFeed = StyleSheet.create({
  feed: {
    width: "95%",
    marginBottom: "5%",
    flexDirection: "row",
    alignItems: "center"
  },
  text: {
    width: "100%"
  }
});

const feedWithImage = StyleSheet.create({
  feed: { ...defaultFeed.feed, justifyContent: "space-between" },
  text: { width: "70%" }
});

export function feedStyle(feed: FeedModel) {
  return feed.image.length > 0 ? feedWithImage : defaultFeed;
}

export const feedScreenStyles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center"
  },
  feedContainer: {
    marginTop: "5%",
    marginLeft: "5%",
    width: "100%"
  },
  feedTitle: {
    fontSize: 18,
    fontWeight: "700",
    maxWidth: "90%",
    marginBottom: "2%"
  },
  feedImage: {
    borderRadius: 20,
    width: 100,
    height: 100
  }
});

