import localization from "@Assets/localization";
import Text from "@Components/Themed/Text";
import View from "@Components/Themed/View";
import { AntDesign } from "@expo/vector-icons";
import TimerModel from "@Models/Timer";
import { useStore } from "@Stores/main";
import { LinearGradient } from "expo-linear-gradient";
import * as React from "react";
import { TouchableOpacity } from "react-native";

import timerCardStyle from "./style";

interface Props {
  timer: TimerModel;
  onPress: () => void;
  editCallback: () => void;
  deleteCallback: () => void;
}

function TimerCard(props: Props) {
  const { timer, onPress, editCallback, deleteCallback } = props;
  const { languageStore } = useStore();

  localization.setLanguage(languageStore.language);

  const timerField = (field: string, value: string) => {
    return (
      <View style={timerCardStyle.timerField}>
        <Text style={timerCardStyle.timerFiledText}>{field}</Text>
        <Text style={timerCardStyle.timerFiledText}>{value}</Text>
      </View>
    );
  };

  const getTime = (minutes: string, seconds: string) => {
    minutes = minutes.length > 1 ? minutes : "0" + minutes;
    seconds = seconds.length > 1 ? seconds : "0" + seconds;
    return `${minutes}:${seconds}`;
  };

  return (
    <TouchableOpacity onPress={onPress} style={timerCardStyle.container}>
      <LinearGradient
        colors={["#ee0d74", "#ff6606"]}
        start={{ x: 0, y: 0.5 }}
        end={{ x: 1, y: 1 }}
        style={timerCardStyle.wrapper}
      >
        <View style={timerCardStyle.upperPart}>
          <Text numberOfLines={1} style={timerCardStyle.title}>
            {timer.title}
          </Text>
          <AntDesign name="edit" size={30} color="white" onPress={editCallback} />
        </View>
        <View style={{ ...timerCardStyle.color, backgroundColor: timer.color }} />
        <View style={timerCardStyle.bottomPart}>
          {timerField(localization.work, getTime(timer.workMinutes, timer.workSeconds))}
          {timerField(localization.colldown, getTime(timer.cooldownMinutes, timer.cooldownSeconds))}
          {timerField(localization.rounds, timer.rounds)}
          <AntDesign name="delete" size={30} color="white" onPress={deleteCallback} />
        </View>
      </LinearGradient>
    </TouchableOpacity>
  );
}

export default TimerCard;
