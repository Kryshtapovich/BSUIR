import { StyleSheet } from "react-native";

const timerCardStyle = StyleSheet.create({
  container: {
    shadowColor: "black",
    shadowOffset: {
      width: 0,
      height: 7
    },
    shadowOpacity: 0.7,
    shadowRadius: 5
  },
  wrapper: {
    padding: 10,
    marginTop: 15,
    borderRadius: 10,
    width: "90%",
    height: 130,
    alignSelf: "center",
    flexDirection: "column",
    justifyContent: "space-between"
  },
  upperPart: {
    flexDirection: "row",
    backgroundColor: "transparent",
    justifyContent: "space-between"
  },
  color: {
    height: 15,
    borderRadius: 20,
    width: "100%"
  },
  bottomPart: {
    flexDirection: "row",
    justifyContent: "space-between",
    backgroundColor: "transparent",
    alignItems: "flex-end"
  },
  timerField: {
    backgroundColor: "transparent",
    alignItems: "center"
  },
  timerFiledText: {
    fontSize: 18,
    color: "white"
  },
  title: {
    fontSize: 25,
    fontWeight: "bold",
    color: "white",
    maxWidth: "90%"
  }
});

export default timerCardStyle;
