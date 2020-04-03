import React from "react";
import { StyleProp, View, ViewStyle } from "react-native";

import { scientificButtons } from "../../../Assets/Buttons";
import Button from "../../Button";
import { scientificStyle } from "./style";

interface Props {
  style?: StyleProp<ViewStyle>;
}

function ScientificMode(props: Props) {
  return (
    <View style={{ ...scientificStyle.scientificMode, ...(props.style as object) }}>
      {scientificButtons.map((arr, i) => (
        <View style={scientificStyle.innerBlock} key={i.toString() + arr.toLocaleString()}>
          {arr.map((item) => (
            <Button key={item.title} buttonStyle={scientificStyle.button} {...item} />
          ))}
        </View>
      ))}
    </View>
  );
}

export default ScientificMode;
