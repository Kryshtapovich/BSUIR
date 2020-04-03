import { StyleSheet } from "react-native";

export const screenStyle = StyleSheet.create({
  screen: {
    flex: 1,
    justifyContent: "flex-end"
  },
  portraitMode: {
    height: "65%",
    marginBottom: "1.5%",
    marginLeft: "2%",
    marginRight: "2%"
  },
  landscapeMode: {
    height: "65%",
    marginBottom: "1.5%"
  },
  textArea: {
    justifyContent: "space-between",
    height: "30%"
  },
  version: {
    justifyContent: "flex-start",
    textAlign: "center",
    fontSize: 15
  },
  result: {
    alignSelf: "flex-end",
    margin: "2%"
  }
});
