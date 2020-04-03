import { Text, View } from "@Components/Themed";
import { faWifi } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-native-fontawesome";
import NetInfo, { NetInfoStateType } from "@react-native-community/netinfo";
import { useStore } from "@Stores/main";
import React, { useEffect } from "react";

import screenTitleStye from "./style";

interface Props {
  title: string;
}

function ScreenTitle(props: Props) {
  const { versionStore } = useStore();
  const connection = NetInfo.useNetInfo();
  const color = connection.type === NetInfoStateType.none ? "red" : "#00e278";

  useEffect(() => {
    versionStore.init();
  }, [versionStore]);

  return (
    <View style={screenTitleStye.wrapper}>
      <Text style={screenTitleStye.title}>{props.title}</Text>
      {props.title === "Feeds" && <FontAwesomeIcon icon={faWifi} size={20} color={color} />}
      {props.title === "URLs" && (
        <Text style={screenTitleStye.version}>{versionStore.version}</Text>
      )}
    </View>
  );
}

export default ScreenTitle;
