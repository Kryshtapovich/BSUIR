import { ThemeProps } from "@Utils/Types";
import * as React from "react";
import { TextInput as DefaultTextInput } from "react-native";

type TextInputProps = ThemeProps & DefaultTextInput["props"];

function TextInput(props: TextInputProps) {
  const { style, ...rest } = props;

  return (
    <DefaultTextInput style={[{ color: "white", backgroundColor: "#83878d" }, style]} {...rest} />
  );
}

export default TextInput;
