import React from "react";
import { StyleProp, Text, ViewStyle } from "react-native";

interface Props {
  content: string;
  style?: StyleProp<ViewStyle>;
}

function Display(props: Props) {
  return (
    <Text adjustsFontSizeToFit numberOfLines={1} style={props.style}>
      {props.content}
    </Text>
  );
}

export default Display;
