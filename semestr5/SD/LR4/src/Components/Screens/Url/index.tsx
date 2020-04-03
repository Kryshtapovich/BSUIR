import Button from "@Components/Button";
import { Text, View } from "@Components/Themed";
import { faPlus, faTrash } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-native-fontawesome";
import UrlModel from "@Models/Url";
import { useStore } from "@Stores/main";
import { observer } from "mobx-react-lite";
import React, { useEffect, useState } from "react";
import { Modal, Pressable, TextInput } from "react-native";
import { ScrollView } from "react-native-gesture-handler";

import urlScreenStyles from "./style";

function UrlScrceen() {
  const [isModalVisible, setIsModalVisible] = useState(false);
  const [newUrl, setNewUrl] = useState("");
  const [activeUrl, setUrl] = useState<UrlModel>();
  const { urlStore, feedStore } = useStore();

  useEffect(() => {
    urlStore.init();
  }, [urlStore]);

  const toggleModal = () => {
    setIsModalVisible(!isModalVisible);
  };

  const handleAddUrl = () => {
    toggleModal();
    setNewUrl("");
    urlStore.addUrl(newUrl);
  };

  const handleDelete = (url: UrlModel) => {
    urlStore.deleteUrl(url);
    feedStore.setUrl(null);
  };

  const style = (url: UrlModel) => {
    const activeFlag = activeUrl === url;
    return {
      wrapper: activeFlag ? urlScreenStyles.activeWrapper : urlScreenStyles.defaultWrapper,
      url: activeFlag ? urlScreenStyles.activeUrl : urlScreenStyles.defaultUrl
    };
  };

  const choose = (url: UrlModel) => {
    setUrl(url);
    feedStore.setUrl(url);
  };

  return (
    <View style={urlScreenStyles.container}>
      <ScrollView style={urlScreenStyles.urlList}>
        {urlStore.urls.map((x) => (
          <Pressable style={style(x).wrapper} onPress={() => choose(x)} key={x.id}>
            <Text numberOfLines={1} style={style(x).url}>
              {x.url}
            </Text>
            <Pressable onPress={() => handleDelete(x)}>
              <FontAwesomeIcon icon={faTrash} color="red" size={20} />
            </Pressable>
          </Pressable>
        ))}
      </ScrollView>

      <Modal animationType="slide" transparent visible={isModalVisible} onDismiss={toggleModal}>
        <View style={urlScreenStyles.modalWrapper}>
          <View style={urlScreenStyles.modalView}>
            <TextInput
              value={newUrl}
              onChange={(e) => setNewUrl(e.nativeEvent.text)}
              style={urlScreenStyles.input}
            />
            <View style={urlScreenStyles.modalButtons}>
              <Button
                text="Add"
                onPress={handleAddUrl}
                style={urlScreenStyles.addButton}
                textStyle={urlScreenStyles.addButtonText}
              />
              <Button
                text="Cancel"
                onPress={toggleModal}
                style={urlScreenStyles.cancelButton}
                textStyle={urlScreenStyles.cancelButtonText}
              />
            </View>
          </View>
        </View>
      </Modal>

      <Pressable onPress={toggleModal} style={urlScreenStyles.showButton}>
        <FontAwesomeIcon icon={faPlus} color="white" size={25} />
      </Pressable>
    </View>
  );
}

export default observer(UrlScrceen);
