import Timer from "@Components/Screens/Timer";
import TimerFormScreen from "@Components/Screens/TimerForm";
import { DarkTheme, DefaultTheme, NavigationContainer } from "@react-navigation/native";
import { createNativeStackNavigator } from "@react-navigation/native-stack";
import { useStore } from "@Stores/main";
import { RootStackParamList } from "@Utils/Types";
import { observer } from "mobx-react-lite";
import * as React from "react";

import BottomTabNavigator from "./BottomTabNavigator";

function Navigation() {
  const { themeStore } = useStore();

  return (
    <NavigationContainer theme={themeStore.theme === "dark" ? DarkTheme : DefaultTheme}>
      <RootNavigator />
    </NavigationContainer>
  );
}

export default observer(Navigation);

const Stack = createNativeStackNavigator<RootStackParamList>();

function RootNavigator() {
  return (
    <Stack.Navigator>
      <Stack.Screen name="Root" component={BottomTabNavigator} options={{ headerShown: false }} />
      <Stack.Screen
        name="TimerForm"
        component={TimerFormScreen}
        options={{ title: "", headerBackTitle: "" }}
      />
      <Stack.Screen
        name="Timer"
        component={Timer}
        options={({ route }) => ({
          title: route.params.timer.title,
          headerBackTitle: ""
        })}
      />
    </Stack.Navigator>
  );
}
