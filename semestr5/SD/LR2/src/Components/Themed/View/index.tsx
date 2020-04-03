import { useStore } from "@Stores/main";
import { ThemeProps } from "@Utils/Types";
import { observer } from "mobx-react-lite";
import * as React from "react";
import { View as DefaultView } from "react-native";

type ViewProps = ThemeProps & DefaultView["props"];

function View(props: ViewProps) {
  const { style, lightColor, darkColor, ...rest } = props;
  const { themeStore } = useStore();

  const backgroundColor = themeStore.theme === "dark" ? darkColor : lightColor;

  return <DefaultView style={[{ backgroundColor }, style]} {...rest} />;
}

export default observer(View);
