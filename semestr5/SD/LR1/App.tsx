import { observer } from "mobx-react-lite";
import React, { useEffect } from "react";
import { StyleSheet, View } from "react-native";

import Display from "./Components/Display";
import LandscapeMode from "./Components/Modes/Landscape";
import UsualMode from "./Components/Modes/Usual";
import usePortrait from "./Hooks/usePortrait";
import { useStore } from "./Stores";
import { screenStyle } from "./style";

function App() {
  const isPortrait = usePortrait();

  const {
    themeStore: { activeTheme },
    calculatorStore: { textResult },
    versionStore
  } = useStore();

  useEffect(() => {
    versionStore.init();
  }, [versionStore]);

  const style = StyleSheet.create({
    ...screenStyle,
    screen: {
      ...screenStyle.screen,
      backgroundColor: activeTheme.background
    },
    version: {
      ...screenStyle.version,
      color: activeTheme.color
    },
    result: {
      ...screenStyle.result,
      fontSize: isPortrait ? 90 : 50,
      color: activeTheme.color
    }
  });

  const showData = () => {
    const data = isPortrait ? textResult(9) : textResult();
    return data;
  };

  return (
    <View style={style.screen}>
      <View style={style.textArea}>
        <Display content={versionStore.version} style={style.version} />
        <Display content={showData()} style={style.result} />
      </View>
      {isPortrait ? (
        <UsualMode style={style.portraitMode} />
      ) : (
        <LandscapeMode style={style.landscapeMode} />
      )}
    </View>
  );
}

export default observer(App);
