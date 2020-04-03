import { StyleSheet } from "react-native";

export const formScreenStyle = StyleSheet.create({
  container: {
    flexDirection: "column",
    width: "95%",
    alignSelf: "center"
  },
  navbar: {
    marginTop: 15,
    alignItems: "center",
    justifyContent: "space-between",
    flexDirection: "row"
  },
  title: {
    fontSize: 30,
    fontWeight: "800",
    color: "#f7393e"
  },
  form: {
    height: "100%",
    marginTop: 5
  },
  fieldWrapper: {
    marginBottom: 15
  },
  textField: {
    color: "#a93567"
  }
});
