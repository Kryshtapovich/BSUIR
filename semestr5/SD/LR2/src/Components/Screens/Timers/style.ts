import { StyleSheet } from "react-native";

const timersStyle = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center"
  },
  timers: {
    width: "100%"
  },
  title: {
    fontSize: 20,
    fontWeight: "bold"
  },
  addButton: {
    position: "absolute",
    backgroundColor: "white",
    borderRadius: 50,
    right: 15,
    bottom: 15
  }
});

export default timersStyle;
