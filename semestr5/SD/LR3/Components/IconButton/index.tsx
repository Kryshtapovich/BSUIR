import { IconProp } from "@fortawesome/fontawesome-svg-core";
import { FontAwesomeIcon, FontAwesomeIconStyle } from "@fortawesome/react-native-fontawesome";
import { LinearGradient, LinearGradientProps } from "expo-linear-gradient";
import React from "react";
import { GestureResponderEvent, StyleProp, TouchableOpacity, ViewStyle } from "react-native";

import { iconButtonStyle } from "./style";

interface Props {
  icon: IconProp;
  iconSize?: number;
  gradientProps?: LinearGradientProps;
  iconStyle?: FontAwesomeIconStyle;
  buttonStyle?: StyleProp<ViewStyle>;
  onPress?: (event: GestureResponderEvent) => void;
}

function IconButton(props: Props) {
  const icon = <FontAwesomeIcon icon={props.icon} size={props.iconSize} style={props.iconStyle} />;
  let gradientWrappedIcon: JSX.Element | null = null;

  if (props.gradientProps) {
    const { style, ...rest } = props.gradientProps;
    gradientWrappedIcon = (
      <LinearGradient style={[iconButtonStyle.gradeientWrapper, style]} {...rest}>
        {icon}
      </LinearGradient>
    );
  }

  return (
    <TouchableOpacity style={props.buttonStyle} onPress={props.onPress}>
      {props.gradientProps ? gradientWrappedIcon : icon}
    </TouchableOpacity>
  );
}

export default IconButton;
