import React from "react";
import { Pressable, PressableProps, StyleProp, Text, TextStyle } from "react-native";

import buttonStyle from "./style";

interface Props {
  text: string;
  textStyle?: StyleProp<TextStyle>;
}

function Button(props: PressableProps & Props) {
  return (
    <Pressable {...props}>
      <Text style={[{ ...buttonStyle.text }, props.textStyle]}>{props.text}</Text>
    </Pressable>
  );
}

export default Button;
