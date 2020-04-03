import { useStore } from "@Stores/main";
import { Themes } from "@Utils/Colors";
import { ThemeProps } from "@Utils/Types";
import { observer } from "mobx-react-lite";
import * as React from "react";
import { Text as DefaultText } from "react-native";

type TextProps = ThemeProps & DefaultText["props"];

function Text(props: TextProps) {
  const { style, lightColor, darkColor, ...rest } = props;
  const { themeStore, fontStore } = useStore();
  const fontSize = (props.style as any).fontSize * fontStore.scale;
  const color = themeStore.theme === "dark" ? Themes.dark.text : Themes.light.text;

  return <DefaultText style={[{ color }, style, { fontSize }]} {...rest} />;
}

export default observer(Text);
