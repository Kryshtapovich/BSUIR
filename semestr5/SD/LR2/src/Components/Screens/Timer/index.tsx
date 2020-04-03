import View from "@Components/Themed/View";
import { AntDesign } from "@expo/vector-icons";
import audioService from "@Services/Audio";
import { useStore } from "@Stores/main";
import { RootTabScreenProps } from "@Utils/Types";
import { observer } from "mobx-react-lite";
import React, { useEffect, useState } from "react";
import { Animated } from "react-native";
import { CountdownCircleTimer } from "react-native-countdown-circle-timer";

import timerStyle from "./style";

function Timer({ route }: RootTabScreenProps<"Timer">) {
  const timer = route.params.timer;
  const { sessionStore } = useStore();
  const [duration, setDuration] = useState(0);
  const [isRunning, setIsRunning] = useState(false);
  const [timerRepeat, setTimerRepeat] = useState(0);

  useEffect(() => {
    sessionStore.init(timer);
    audioService.configure();
    return () => {
      sessionStore.dispose();
      audioService.dispose();
    };
  }, [sessionStore.total]);

  const toggleRunning = () => {
    setIsRunning(!isRunning);
  };

  const reset = () => {
    sessionStore.reset();
    setIsRunning(false);
    setDuration(sessionStore.time);
    setTimerRepeat(timerRepeat + 1);
  };

  const next = (): [boolean, number] => {
    audioService.play();
    if (sessionStore.notEnd) {
      sessionStore.isReseted && sessionStore.next();
      setDuration(sessionStore.time);
      setTimerRepeat(timerRepeat + 1);
      !sessionStore.isReseted && sessionStore.next();
      return [sessionStore.notEnd, 0];
    } else {
      return [false, 0];
    }
  };

  const chechEnd = async (remainingTime: number) => {
    if (isRunning && !remainingTime && !sessionStore.notEnd) setIsRunning(false);
  };

  const formatTime = (time: number) => {
    let minutes = Math.floor(time / 60).toString();
    let seconds = (time % 60).toString();
    minutes = minutes.length < 2 ? "0" + minutes : minutes;
    seconds = seconds.length < 2 ? "0" + seconds : seconds;
    return minutes + ":" + seconds;
  };

  const animatedText = (text: string, color: string) => (
    <Animated.Text style={{ fontSize: 40, color }}>{text}</Animated.Text>
  );

  return (
    <View style={timerStyle.container}>
      <CountdownCircleTimer
        size={320}
        isPlaying={isRunning}
        key={timerRepeat}
        duration={duration}
        trailColor="#789fc9c7"
        colors={[
          [timer.color, 0.9],
          ["#A30000", 0.1]
        ]}
        onComplete={next}
      >
        {({ remainingTime, animatedColor }) => {
          chechEnd(remainingTime);
          return (
            <View style={timerStyle.timerText}>
              {animatedText(formatTime(remainingTime), animatedColor)}
              {animatedText(sessionStore.phase, animatedColor)}
            </View>
          );
        }}
      </CountdownCircleTimer>
      <View style={timerStyle.controls}>
        {isRunning ? (
          <AntDesign name="pausecircle" color="#8000ff" size={60} onPress={toggleRunning} />
        ) : (
          <AntDesign name="rightcircle" color="#8000ff" size={60} onPress={toggleRunning} />
        )}
        <AntDesign name="closecircle" color="#8000ff" size={60} onPress={reset} />
      </View>
    </View>
  );
}

export default observer(Timer);
