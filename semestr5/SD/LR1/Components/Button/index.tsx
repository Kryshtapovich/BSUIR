import { observer } from "mobx-react-lite";
import React from "react";
import { Platform, StyleSheet, Text, TouchableOpacity, View } from "react-native";

import { ButtonModel } from "../../Assets/Buttons";
import { useStore } from "../../Stores";
import { buttonStyle } from "./style";

function Button(props: ButtonModel) {
  const {
    themeStore: { activeTheme, isLight },
    calculatorStore: { operation, isProcessing }
  } = useStore();

  let timer: NodeJS.Timer;
  let flag = operation && operation === props.title && isProcessing;

  const style = StyleSheet.create({
    button: {
      ...buttonStyle.button,
      backgroundColor: flag ? activeTheme.color : activeTheme.background,
      ...Platform.select({
        ios: {
          shadowColor: activeTheme.color,
          shadowOffset: isLight ? { width: 5, height: 5, } : {width: 0, height : 0},
          shadowOpacity: isLight ? 0.7 : 1,
        },
        android: {
          borderColor: flag ? activeTheme.color : activeTheme.androidBorder,
          opacity: 5,
          borderWidth: 5
        }
      }),
      ...(props.buttonStyle as object)
    },
    text: {
      ...buttonStyle.text,
      color: flag ? activeTheme.background : activeTheme.color,
      ...(props.textStyle as object)
    },
    superScript: {
      ...buttonStyle.superScript,
      color: flag ? activeTheme.background : activeTheme.color
    }
  });

  const buttonContent = (
    <View style={{ flexDirection: "row" }}>
      <Text adjustsFontSizeToFit style={style.text}>
        {props.title}
      </Text>
      {props.superScript && <Text style={style.superScript}>{props.superScript}</Text>}
    </View>
  );

  return props.canLongPress ? (
    <TouchableOpacity
      style={style.button}
      onPress={props.onPress}
      onLongPress={() => {
        timer = setInterval(() => props.onPress(), 120);
      }}
      onPressOut={() => clearInterval(timer)}
    >
      {buttonContent}
    </TouchableOpacity>
  ) : (
    <TouchableOpacity style={style.button} onPress={props.onPress}>
      {buttonContent}
    </TouchableOpacity>
  );
}

export default observer(Button);
