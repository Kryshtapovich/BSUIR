import { StyleSheet } from "react-native";

const settingsStyle = StyleSheet.create({
  container: {
    flex: 1,
    width: "100%",
    alignItems: "center"
  },
  theme: {
    flexDirection: "row",
    justifyContent: "space-between",
    width: "90%",
    alignItems: "center",
    marginTop: 15
  },
  fontBlock: {
    marginTop: 15,
    width: "90%"
  },
  textBlock: {
    marginTop: 10,
    flexDirection: "row",
    justifyContent: "space-around",
    alignItems: "center"
  },
  smallText: {
    fontSize: 15
  },
  normalText: {
    fontSize: 20
  },
  hugeText: {
    fontSize: 25
  },
  languageBlock: {
    marginTop: 15,
    width: "90%"
  },
  textWrapper: {
    padding: 10,
    borderWidth: 2,
    borderColor: "green",
    borderRadius: 10
  },
  version: {
    marginTop: "60%",
    fontSize: 15,
    alignSelf: "center"
  },
});

export default settingsStyle;
