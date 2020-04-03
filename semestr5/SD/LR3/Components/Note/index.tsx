import IconButton from "@Components/IconButton";
import { faTrash } from "@fortawesome/free-solid-svg-icons";
import useOrientation from "@Hooks/useOrientation";
import NoteModel from "@Models/Note";
import { mainGradient } from "@utils/shared";
import { LinearGradient } from "expo-linear-gradient";
import React from "react";
import { GestureResponderEvent, Text, TouchableOpacity, View } from "react-native";

import { landscapeStyle, portraitStyle } from "./style";

interface Props {
  note: NoteModel;
  onPress: (event: GestureResponderEvent) => void;
  deleteCallback: (event: GestureResponderEvent) => void;
}

function Note(props: Props) {
  const orientation = useOrientation();
  const noteStyle = orientation.isPortrait ? portraitStyle : landscapeStyle;

  return (
    <TouchableOpacity style={noteStyle.container} onPress={props.onPress}>
      <LinearGradient {...mainGradient} style={noteStyle.note}>
        <View style={noteStyle.header}>
          <Text numberOfLines={1} style={noteStyle.title}>
            {props.note.title}
          </Text>
          <IconButton
            icon={faTrash}
            iconSize={22}
            iconStyle={{ color: "white" }}
            buttonStyle={noteStyle.deleteButton}
            onPress={props.deleteCallback}
          />
        </View>
        <Text numberOfLines={4} style={noteStyle.description}>
          {props.note.description}
        </Text>
      </LinearGradient>
    </TouchableOpacity>
  );
}

export default Note;
