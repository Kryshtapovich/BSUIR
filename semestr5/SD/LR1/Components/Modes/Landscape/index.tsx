import React from "react";
import { StyleProp, View, ViewStyle } from "react-native";

import ScientificMode from "../Scientific";
import UsualMode from "../Usual";
import { landscapeStyle } from "./style";

interface Props {
  style?: StyleProp<ViewStyle>;
}

function LandscapeMode(props: Props) {
  return (
    <View style={{ ...landscapeStyle.landscapeMode, ...(props.style as object) }}>
      <ScientificMode style={landscapeStyle.scientificMode} />
      <UsualMode style={landscapeStyle.usualMode} />
    </View>
  );
}

export default LandscapeMode;
