import localization from "@Assets/localization";
import Text from "@Components/Themed/Text";
import View from "@Components/Themed/View";
import { Feather } from "@expo/vector-icons";
import { useStore } from "@Stores/main";
import { observer } from "mobx-react-lite";
import * as React from "react";
import { StyleProp, TextStyle, ViewStyle } from "react-native";
import { TouchableOpacity } from "react-native-gesture-handler";

import settingsStyle from "./style";

function SettingsScreen() {
  const { themeStore, fontStore, languageStore, versionStore } = useStore();
  localization.setLanguage(languageStore.language);

  React.useEffect(() => {
    versionStore.init();
  }, [versionStore]);

  const themeIcon =
    themeStore.theme === "dark" ? (
      <Feather name="moon" size={40} color="white" onPress={() => themeStore.setTheme("light")} />
    ) : (
      <Feather name="sun" size={40} color="black" onPress={() => themeStore.setTheme("dark")} />
    );

  return (
    <View style={settingsStyle.container}>
      <View style={settingsStyle.theme}>
        <Text style={settingsStyle.normalText}>{localization.theme}</Text>
        {themeIcon}
      </View>
      <View style={settingsStyle.fontBlock}>
        <Text style={settingsStyle.normalText}>{localization.fontSize}</Text>
        <View style={settingsStyle.textBlock}>
          <TextButton
            buttonStyle={fontStore.scale === 0.8 && settingsStyle.textWrapper}
            textStyle={settingsStyle.smallText}
            text={localization.small}
            onPress={() => fontStore.setScale(0.8)}
          />
          <TextButton
            buttonStyle={fontStore.scale === 1 && settingsStyle.textWrapper}
            text={localization.normal}
            onPress={() => fontStore.setScale(1)}
          />
          <TextButton
            buttonStyle={fontStore.scale === 1.2 && settingsStyle.textWrapper}
            textStyle={settingsStyle.hugeText}
            text={localization.huge}
            onPress={() => fontStore.setScale(1.2)}
          />
        </View>
      </View>
      <View style={settingsStyle.languageBlock}>
        <Text style={settingsStyle.normalText}>{localization.language}</Text>
        <View style={settingsStyle.textBlock}>
          <TextButton
            onPress={() => languageStore.setLanguage("en")}
            buttonStyle={languageStore.language === "en" && settingsStyle.textWrapper}
            text={localization.english}
          />
          <TextButton
            onPress={() => languageStore.setLanguage("ru")}
            buttonStyle={languageStore.language === "ru" && settingsStyle.textWrapper}
            text={localization.russian}
          />
        </View>
      </View>
      <Text style={settingsStyle.version}>{versionStore.version}</Text>
    </View>
  );
}

export default observer(SettingsScreen);
interface TextButtonProps {
  text: string;
  onPress: () => void;
  textStyle?: StyleProp<TextStyle>;
  buttonStyle: StyleProp<ViewStyle>;
}

function TextButton(props: TextButtonProps) {
  const { buttonStyle, text, onPress } = props;
  const textStyle = props.textStyle ? props.textStyle : settingsStyle.normalText;
  return (
    <TouchableOpacity style={buttonStyle} onPress={onPress}>
      <Text style={textStyle}>{text}</Text>
    </TouchableOpacity>
  );
}
