import IconButton from "@Components/IconButton";
import TextField from "@Components/TextField";
import { faCheck, faLongArrowAltLeft } from "@fortawesome/free-solid-svg-icons";
import { NavigationParams } from "@Models/NavigationParams";
import { NativeStackScreenProps } from "@react-navigation/native-stack";
import { mainGradient } from "@utils/shared";
import React, { useState } from "react";
import { ScrollView, Text, TextInputProps, View } from "react-native";

import { formScreenStyle } from "./style";

function FormScreen(props: NativeStackScreenProps<NavigationParams, "Form">) {
  const { note, submitCallback } = props.route.params;
  const [title, setTitle] = useState(note ? note.title : "");
  const [description, setDescription] = useState(note ? note.description : "");
  const [tags, setTags] = useState(note ? note.tags : "");
  const gradientProps = { ...mainGradient, style: formScreenStyle.fieldWrapper };

  const submit = () => {
    const newNote = {
      id: note ? note.id : "",
      title: title.length ? title : new Date().toLocaleString("ru-Ru"),
      description: description,
      tags: tags
    };
    submitCallback(newNote);
    props.navigation.goBack();
  };

  const textFields: TextInputProps[] = [
    {
      placeholder: "Title",
      value: title,
      style: formScreenStyle.textField,
      onChange: (event) => setTitle(event.nativeEvent.text)
    },
    {
      placeholder: "Description",
      value: description,
      style: formScreenStyle.textField,
      onChange: (event) => setDescription(event.nativeEvent.text)
    },
    {
      placeholder: "Tags",
      value: tags,
      style: formScreenStyle.textField,
      onChange: (event) => setTags(event.nativeEvent.text)
    }
  ];

  return (
    <View style={formScreenStyle.container}>
      <View style={formScreenStyle.navbar}>
        <IconButton
          icon={faLongArrowAltLeft}
          iconSize={30}
          iconStyle={{ color: "#f7393e" }}
          onPress={() => props.navigation.goBack()}
        />
        <Text style={formScreenStyle.title}>Notes</Text>
        <IconButton
          icon={faCheck}
          iconSize={30}
          iconStyle={{ color: "#0df27f" }}
          onPress={submit}
        />
      </View>
      <ScrollView style={formScreenStyle.form}>
        {textFields.map((field, i) => (
          <TextField key={i} gradientWrapperProps={gradientProps} textInputProps={field} />
        ))}
      </ScrollView>
    </View>
  );
}

export default FormScreen;
