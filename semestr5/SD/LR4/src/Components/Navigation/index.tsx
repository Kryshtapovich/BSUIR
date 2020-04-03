import FeedScreen from "@Components/Screens/Feed";
import UrlScreen from "@Components/Screens/Url";
import ScreenTitle from "@Components/ScreenTitle";
import { createDrawerNavigator } from "@react-navigation/drawer";
import { DarkTheme, DefaultTheme, NavigationContainer } from "@react-navigation/native";
import LinkingConfiguration from "@Utils/LinkingConfiguration";
import * as React from "react";
import { ColorSchemeName } from "react-native";

const Drawer = createDrawerNavigator();

export default function Navigation({ colorScheme }: { colorScheme: ColorSchemeName }) {
  return (
    <NavigationContainer
      linking={LinkingConfiguration}
      theme={colorScheme === "dark" ? DarkTheme : DefaultTheme}
    >
      <Drawer.Navigator initialRouteName="URLs">
        <Drawer.Screen
          options={{
            headerTitle: () => <ScreenTitle title="Feeds" />
          }}
          name="Feeds"
          component={FeedScreen}
        />
        <Drawer.Screen
          options={{
            headerTitle: () => <ScreenTitle title="URLs" />
          }}
          name="URLs"
          component={UrlScreen}
        />
      </Drawer.Navigator>
    </NavigationContainer>
  );
}
