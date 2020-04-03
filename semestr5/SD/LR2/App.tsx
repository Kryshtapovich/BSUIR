import Navigation from "@Components/Navigation";
import { observer } from "mobx-react-lite";
import React from "react";
import { SafeAreaProvider } from "react-native-safe-area-context";

function App() {
  return (
    <SafeAreaProvider>
      <Navigation />
    </SafeAreaProvider>
  );
}

export default observer(App);
