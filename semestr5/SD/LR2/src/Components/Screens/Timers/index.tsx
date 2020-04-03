import localization from "@Assets/localization";
import View from "@Components/Themed/View";
import TimerCard from "@Components/TimerCard";
import { AntDesign } from "@expo/vector-icons";
import { useStore } from "@Stores/main";
import { RootTabScreenProps } from "@Utils/Types";
import { observer } from "mobx-react-lite";
import * as React from "react";
import { Pressable, ScrollView } from "react-native";

import timersStyle from "./style";

function TimersScreen({ navigation }: RootTabScreenProps<"Timers">) {
  const { timerStore, languageStore } = useStore();

  React.useEffect(() => {
    timerStore.init();
    localization.setLanguage(languageStore.language);
    return () => timerStore.dispose();
  }, [timerStore, languageStore.language]);

  return (
    <View style={timersStyle.container}>
      <ScrollView style={timersStyle.timers}>
        {timerStore.timers.map((x) => (
          <TimerCard
            key={x.id}
            timer={x}
            onPress={() => navigation.navigate("Timer", { timer: x })}
            editCallback={() =>
              navigation.navigate("TimerForm", {
                timer: x,
                callback: (x) => timerStore.editTimer(x)
              })
            }
            deleteCallback={() => timerStore.deleteTimer(x)}
          />
        ))}
      </ScrollView>
      <Pressable
        onPress={() =>
          navigation.navigate("TimerForm", { callback: (timer) => timerStore.addTimer(timer) })
        }
        style={timersStyle.addButton}
      >
        <AntDesign name="pluscircle" color="#00fa9a" size={50} />
      </Pressable>
    </View>
  );
}

export default observer(TimersScreen);
