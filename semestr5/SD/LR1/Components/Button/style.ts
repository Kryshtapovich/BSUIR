import { Platform, StyleSheet } from "react-native";

export const buttonStyle = StyleSheet.create({
  button: {
    justifyContent: "center",
    alignItems: "center",
    width: "100%",
    height: "100%",
    borderRadius: 100,
    ...Platform.select({
      ios: {
        shadowRadius: 5
      },
      android: {
        opacity: 5,
        borderWidth: 5
      }
    })
  },
  text: {
    fontSize: 25,
    fontWeight: "bold"
  },
  superScript: {
    fontSize: 12,
    lineHeight: 15,
    fontWeight: "bold"
  }
});
