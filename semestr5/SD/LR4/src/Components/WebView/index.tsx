import { faArrowLeft } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-native-fontawesome";
import React, { useState } from "react";
import { Pressable } from "react-native";
import { WebView as DefaultWebView } from "react-native-webview";

import webViewStyle from "./style";

interface Props {
  uri: string;
  closeCallback: () => void;
}

function WebView(props: Props) {
  return (
    <>
      <DefaultWebView scalesPageToFit startInLoadingState source={{ uri: props.uri }} />
      <Pressable onPress={props.closeCallback} style={webViewStyle.closeButton}>
        <FontAwesomeIcon icon={faArrowLeft} color="white" size={25} />
      </Pressable>
    </>
  );
}

export default WebView;
