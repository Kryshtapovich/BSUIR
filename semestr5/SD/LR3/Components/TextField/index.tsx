import { LinearGradient, LinearGradientProps } from "expo-linear-gradient";
import React from "react";
import { TextInput, TextInputProps } from "react-native";

import { textFieldStyle } from "./style";

interface Props {
  gradientWrapperProps: LinearGradientProps;
  textInputProps: TextInputProps;
}

function TextField(props: Props) {
  const { style: wrapperStyle, ...wrapperRest } = props.gradientWrapperProps;
  const { style: inputStyle, ...inputRest } = props.textInputProps;

  return (
    <LinearGradient style={[textFieldStyle.gradientWrapper, wrapperStyle]} {...wrapperRest}>
      <TextInput style={[textFieldStyle.input, inputStyle]} multiline {...inputRest} />
    </LinearGradient>
  );
}

export default TextField;
