import { Text, View } from "@Components/Themed";
import WebView from "@Components/WebView";
import FeedModel from "@Models/Feed";
import NetInfo, { NetInfoStateType } from "@react-native-community/netinfo";
import { useStore } from "@Stores/main";
import { observer } from "mobx-react-lite";
import * as React from "react";
import { useEffect, useState } from "react";
import { Image, Pressable } from "react-native";
import { ScrollView } from "react-native-gesture-handler";
import { parse } from "react-native-rss-parser";

import { feedScreenStyles, feedStyle } from "./style";

function FeedScreen() {
  const { feedStore } = useStore();
  const [item, setItem] = useState<FeedModel>();
  const connecntion = NetInfo.useNetInfo();

  useEffect(() => {
    if (connecntion.type !== NetInfoStateType.none) {
      feedStore.url &&
        fetch(feedStore.url.url)
          .then((response) => response.text())
          .then((str) => parse(str))
          .then((list) => feedStore.setFeeds(list.items));
    } else {
      feedStore.url && feedStore.getFeeds();
    }
  }, [feedStore.url, connecntion.type]);

  return item ? (
    <WebView uri={item.link} closeCallback={() => setItem(undefined)} />
  ) : (
    <View style={feedScreenStyles.container}>
      <ScrollView style={feedScreenStyles.feedContainer}>
        {feedStore.feeds.map((x, i) => (
          <Pressable style={feedStyle(x).feed} onPress={() => setItem(x)} key={i}>
            <View style={feedStyle(x).text}>
              <Text style={feedScreenStyles.feedTitle}>{x.title}</Text>
              <Text>{x.date}</Text>
            </View>
            {x.image.length > 0 && (
              <Image style={feedScreenStyles.feedImage} source={{ uri: x.image }} />
            )}
          </Pressable>
        ))}
      </ScrollView>
    </View>
  );
}

export default observer(FeedScreen);
