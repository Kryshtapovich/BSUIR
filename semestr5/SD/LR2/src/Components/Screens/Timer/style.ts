import { StyleSheet } from "react-native";

const timerStyle = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center"
  },
  timerText: {
    alignItems: "center",
    alignSelf: "center",
    justifyContent: "space-between",
    height: "50%"
  },
  controls: {
    marginTop: "10%",
    width: "70%",
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between"
  }
});

export default timerStyle;
