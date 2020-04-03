import { StyleSheet } from "react-native";

const inputStyle = StyleSheet.create({
  input: {
    borderRadius: 8,
    width: 50,
    height: 40,
    fontSize: 25,
    textAlign: "center"
  }
});

const timerFormStyle = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center"
  },
  title: {
    fontSize: 30,
    fontWeight: "bold",
    paddingHorizontal: 15,
    marginVertical: 20,
    width: "100%",
    alignSelf: "center",
    borderRadius: 20,
    height: 50
  },
  form: {
    flex: 1,
    width: "90%"
  },
  formItem: {
    flexDirection: "row",
    width: "100%",
    alignSelf: "center",
    justifyContent: "space-between",
    alignItems: "center",
    marginBottom: 20
  },
  text: {
    fontSize: 30
  },
  inputFields: {
    flexDirection: "row"
  },
  timeInput: {
    ...inputStyle.input
  },
  roundsInput: {
    ...inputStyle.input,
    marginRight: 28
  },
  applyButton: {
    width: "100%",
    height: 45,
    borderRadius: 25,
    alignSelf: "center",
    alignItems: "center",
    justifyContent: "center",
    backgroundColor: "#44cc11",
    marginBottom: 30,
    marginTop: 10
  },
  buttonText: {
    fontSize: 25,
    fontWeight: "bold",
    color: "white"
  },
  colorPicker: {
    flex: 1
  }
});

export default timerFormStyle;
