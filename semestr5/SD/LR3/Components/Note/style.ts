import { StyleSheet } from "react-native";

const defaultStyle = StyleSheet.create({
  container: {
    shadowColor: "black",
    shadowOffset: {
      width: 0,
      height: 7
    },
    shadowOpacity: 0.7,
    shadowRadius: 5
  },
  note: {
    flexDirection: "column",
    borderRadius: 10
  },
  header: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between"
  },
  title: {
    color: "white",
    fontSize: 25,
    fontWeight: "bold",
    marginBottom: "2%",
    maxWidth: "80%"
  },
  deleteButton: {
    position: "absolute",
    right: -10,
    top: -5,
    padding: 10
  },
  description: {
    color: "white",
    maxWidth: "95%",
    fontSize: 15,
    fontWeight: "600"
  }
});

export const portraitStyle = StyleSheet.create({
  ...defaultStyle,
  container: {
    ...defaultStyle.container,
    width: "100%"
  },
  note: {
    ...defaultStyle.note,
    margin: "2%",
    padding: "3%"
  }
});

export const landscapeStyle = StyleSheet.create({
  ...defaultStyle,
  container: {
    ...defaultStyle.container,
    width: "33%"
  },
  note: {
    ...defaultStyle.note,
    margin: "4%",
    padding: "6%"
  }
});
