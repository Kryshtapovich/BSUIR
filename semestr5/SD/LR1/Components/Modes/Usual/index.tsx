import React from "react";
import { StyleProp, View, ViewStyle } from "react-native";

import { usualButtons } from "../../../Assets/Buttons";
import Button from "../../Button";
import { usualStyle } from "./style";

interface Props {
  style?: StyleProp<ViewStyle>;
}

function UsualMode(props: Props) {
  return (
    <View style={{ ...usualStyle.usualMode, ...(props.style as object) }}>
      {usualButtons.map((arr, i) => (
        <View style={usualStyle.innerBlock} key={i.toString() + arr.toLocaleString()}>
          {arr.map((item) => (
            <Button key={item.title} buttonStyle={usualStyle.button} {...item} />
          ))}
        </View>
      ))}
    </View>
  );
}

export default UsualMode;
