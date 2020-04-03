import localization from "@Assets/localization";
import Text from "@Components/Themed/Text";
import TextInput from "@Components/Themed/TextInput";
import View from "@Components/Themed/View";
import TimerModel from "@Models/Timer";
import { useStore } from "@Stores/main";
import { RootTabScreenProps } from "@Utils/Types";
import { StatusBar } from "expo-status-bar";
import * as React from "react";
import { Keyboard, Platform, TextInputProps, TouchableOpacity, TouchableWithoutFeedback } from "react-native";
import { fromHsv, TriangleColorPicker } from "react-native-color-picker";

import timerFormStyle from "./style";

function TimerFormScreen(props: RootTabScreenProps<"TimerForm">) {
  const { languageStore } = useStore();
  const timer = props.route.params.timer;
  const [color, setColor] = React.useState(timer?.color);
  const [title, setTitle] = React.useState(timer?.title);
  const workMinutes = React.useState(timer?.workMinutes);
  const workSeconds = React.useState(timer?.workSeconds);
  const cooldownMinutes = React.useState(timer?.cooldownMinutes);
  const cooldownSeconds = React.useState(timer?.cooldownSeconds);
  const rounds = React.useState(timer?.rounds);

  localization.setLanguage(languageStore.language);

  const getValue = (value: string | undefined) => {
    if (value) return value?.length > 0 ? value : "0";
    else return "0";
  };

  const handleSubmit = () => {
    const newTimer: TimerModel = {
      id: getValue(timer?.id),
      title: title || localization.title,
      color: color || "blue",
      workMinutes: getValue(workMinutes[0]),
      workSeconds: getValue(workSeconds[0]),
      cooldownMinutes: getValue(cooldownMinutes[0]),
      cooldownSeconds: getValue(cooldownSeconds[0]),
      rounds: getValue(rounds[0])
    };
    props.route.params.callback(newTimer);
    props.navigation.goBack();
  };

  return (
    <TouchableWithoutFeedback onPress={Keyboard.dismiss} accessible={false}>
      <View style={timerFormStyle.container}>
        <StatusBar style={Platform.OS === "ios" ? "light" : "auto"} />
        <View style={timerFormStyle.form}>
          <TextInput
            placeholder={localization.title}
            style={timerFormStyle.title}
            value={title}
            onChange={(e) => setTitle(e.nativeEvent.text)}
          />
          <FormItem type={localization.work} timeState={[workMinutes, workSeconds]} />
          <FormItem type={localization.colldown} timeState={[cooldownMinutes, cooldownSeconds]} />
          <FormItem type={localization.rounds} roundsState={rounds} />
          <TriangleColorPicker
            defaultColor={color}
            onColorChange={(color) => setColor(fromHsv(color))}
            hideControls
            style={timerFormStyle.colorPicker}
          />
          <TouchableOpacity style={timerFormStyle.applyButton} onPress={handleSubmit}>
            <Text style={timerFormStyle.buttonText}>{localization.apply}</Text>
          </TouchableOpacity>
        </View>
      </View>
    </TouchableWithoutFeedback>
  );
}

export default TimerFormScreen;

type StateType = [string | undefined, React.Dispatch<React.SetStateAction<string | undefined>>];
interface Props {
  type: string;
  timeState?: StateType[];
  roundsState?: StateType;
}

const FormItem = (props: Props) => {
  const { type, timeState, roundsState } = props;
  const isRounds = type === localization.rounds;

  const enterTime = (
    value: string,
    callback: React.Dispatch<React.SetStateAction<string | undefined>>
  ) => {
    if (parseInt(value) > 59) callback("59");
    else if (isNaN(parseInt(value))) callback(value.substring(0, value.length - 1));
    else callback(value);
  };

  return (
    <View style={timerFormStyle.formItem}>
      <Text style={timerFormStyle.text}>{props.type}</Text>
      <View style={timerFormStyle.inputFields}>
        {isRounds ? (
          <NumberInput
            style={timerFormStyle.roundsInput}
            value={roundsState?.[0]}
            onChange={(e) => roundsState![1](e.nativeEvent.text)}
          />
        ) : (
          <>
            <NumberInput
              value={timeState?.[0][0]}
              onChange={(e) => enterTime(e.nativeEvent.text, timeState![0][1])}
            />
            <Text style={timerFormStyle.text}>:</Text>
            <NumberInput
              value={timeState?.[1][0]}
              onChange={(e) => enterTime(e.nativeEvent.text, timeState![1][1])}
            />
          </>
        )}
      </View>
    </View>
  );
};

const NumberInput = (props: TextInputProps) => {
  const { style, placeholder, ...rest } = props;
  return (
    <TextInput
      keyboardType="number-pad"
      placeholder={placeholder ? placeholder : "00"}
      style={style ? style : timerFormStyle.timeInput}
      maxLength={2}
      {...rest}
    />
  );
};
