import { StyleSheet } from "react-native";

const screenTitleStye = StyleSheet.create({
  wrapper: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
    marginLeft: "38%",
    width: "90%"
  },
  title: {
    fontSize: 20,
    fontWeight: "500"
  },
  version: {
    fontSize: 15
  }
});

export default screenTitleStye;
