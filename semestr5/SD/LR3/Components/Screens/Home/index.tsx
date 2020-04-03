import IconButton from "@Components/IconButton";
import Note from "@Components/Note";
import TextField from "@Components/TextField";
import { faPlus, faSort } from "@fortawesome/free-solid-svg-icons";
import useOrientation from "@Hooks/useOrientation";
import { NavigationParams } from "@Models/NavigationParams";
import { NativeStackScreenProps } from "@react-navigation/native-stack";
import { useStore } from "@Stores/main";
import { buttonGradient, mainGradient } from "@utils/shared";
import { observer } from "mobx-react-lite";
import React, { useEffect, useState } from "react";
import { ScrollView, Text, View } from "react-native";

import { landscapeStyle, portraitStyle } from "./style";

function HomeScreen(props: NativeStackScreenProps<NavigationParams, "Home">) {
  const orientation = useOrientation();
  const homeScreenStyle = orientation.isPortrait ? portraitStyle : landscapeStyle;
  const { noteStore, versionStore } = useStore();
  const [tags, setTags] = useState("");

  const [isSorted, setIsSorted] = useState(false);
  useEffect(() => {
    noteStore.init();
    versionStore.init();
    return () => noteStore.dispose();
  }, [noteStore, versionStore]);

  return (
    <>
      <View style={homeScreenStyle.navbar}>
        <View style={homeScreenStyle.navbarHeader}>
          <IconButton
            icon={faSort}
            iconSize={30}
            iconStyle={{ color: isSorted ? "#f7393e" : "black" }}
            onPress={() => setIsSorted(!isSorted)}
          />
          <Text style={homeScreenStyle.title}>Notes</Text>
          <Text style={homeScreenStyle.version}>{versionStore.version}</Text>
        </View>
        <TextField
          gradientWrapperProps={{
            ...mainGradient,
            style: homeScreenStyle.search
          }}
          textInputProps={{
            placeholder: "Search by tag",
            style: homeScreenStyle.searchInput,
            onChange: (event) => {
              setTags(event.nativeEvent.text);
            }
          }}
        />
      </View>
      <ScrollView contentContainerStyle={homeScreenStyle.notes}>
        {noteStore
          .getNotes(isSorted)
          .filter((note) => note.tags.includes(tags))
          .map((note) => (
            <Note
              key={note.id}
              note={note}
              onPress={() =>
                props.navigation.navigate("Form", {
                  note: note,
                  submitCallback: (note) => noteStore.editNote(note)
                })
              }
              deleteCallback={() => noteStore.deleteNote(note)}
            />
          ))}
      </ScrollView>
      <IconButton
        icon={faPlus}
        iconStyle={{ color: "white" }}
        iconSize={24}
        gradientProps={buttonGradient}
        buttonStyle={homeScreenStyle.addButton}
        onPress={() =>
          props.navigation.navigate("Form", { submitCallback: (note) => noteStore.addNote(note) })
        }
      />
    </>
  );
}

export default observer(HomeScreen);
