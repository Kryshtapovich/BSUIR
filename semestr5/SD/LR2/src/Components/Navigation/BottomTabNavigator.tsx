import localization from "@Assets/localization";
import SettingsScreen from "@Components/Screens/Settings";
import TimersScreen from "@Components/Screens/Timers";
import { Ionicons } from "@expo/vector-icons";
import { createBottomTabNavigator } from "@react-navigation/bottom-tabs";
import { useStore } from "@Stores/main";
import { Themes } from "@Utils/Colors";
import { RootTabParamList } from "@Utils/Types";
import { observer } from "mobx-react-lite";
import * as React from "react";

const BottomTab = createBottomTabNavigator<RootTabParamList>();

function BottomTabNavigator() {
  const { themeStore, languageStore } = useStore();
  localization.setLanguage(languageStore.language);

  return (
    <BottomTab.Navigator
      initialRouteName="Timers"
      screenOptions={{
        tabBarActiveTintColor: Themes[themeStore.theme].tint
      }}
    >
      <BottomTab.Screen
        name="Timers"
        component={TimersScreen}
        options={{
          tabBarIcon: ({ color }) => <Ionicons name="timer-outline" size={30} color={color} />,
          title: localization.timers
        }}
      />
      <BottomTab.Screen
        name="Settings"
        component={SettingsScreen}
        options={{
          tabBarIcon: ({ color }) => <Ionicons name="settings-outline" size={30} color={color} />,
          title: localization.settings
        }}
      />
    </BottomTab.Navigator>
  );
}

export default observer(BottomTabNavigator);
