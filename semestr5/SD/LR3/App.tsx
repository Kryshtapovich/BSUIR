import { NavigationContainer } from "@react-navigation/native";
import { createNativeStackNavigator } from "@react-navigation/native-stack";
import { theme } from "@utils/shared";
import React from "react";
import { Keyboard, TouchableWithoutFeedback } from "react-native";

import FormScreen from "./Components/Screens/Form";
import HomeScreen from "./Components/Screens/Home";

const Stack = createNativeStackNavigator();

export default function App() {
  return (
    <TouchableWithoutFeedback onPress={Keyboard.dismiss} accessible={false}>
      <NavigationContainer theme={theme}>
        <Stack.Navigator screenOptions={{ headerShown: false }}>
          <Stack.Screen name="Home" component={HomeScreen} />
          <Stack.Screen name="Form" component={FormScreen} />
        </Stack.Navigator>
      </NavigationContainer>
    </TouchableWithoutFeedback>
  );
}
