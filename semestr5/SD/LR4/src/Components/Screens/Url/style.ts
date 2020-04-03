import { StyleSheet } from "react-native";

const url = StyleSheet.create({
  text: {
    fontSize: 20,
    maxWidth: "90%",
    marginRight: 10
  }
});

const urlWrapper = StyleSheet.create({
  wrapper: {
    height: 40,
    paddingHorizontal: "2%",
    marginTop: "3%",
    flexDirection: "row",
    justifyContent: "space-between",
    alignSelf: "center",
    alignItems: "center",
    width: "95%",
    borderRadius: 6
  }
});

const urlScreenStyles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center"
  },
  urlList: {
    flex: 1,
    width: "100%"
  },
  defaultWrapper: {
    ...urlWrapper.wrapper
  },
  activeWrapper: {
    ...urlWrapper.wrapper,
    backgroundColor: "rgba(137, 196, 244, 0.4)"
  },
  activeUrl: {
    ...url.text,
    color: "rgba(25, 121, 254, 1)"
  },
  defaultUrl: {
    ...url.text
  },
  deleteButton: {
    backgroundColor: "#e41515",
    color: "white",
    height: 50,
    paddingHorizontal: 10
  },
  modalWrapper: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center",
    backgroundColor: "rgba(0, 0, 0, 0.3)"
  },
  modalView: {
    alignItems: "center",
    justifyContent: "center",
    elevation: 5,
    height: 180,
    width: "80%",
    borderColor: "#0278da",
    borderWidth: 1,
    borderRadius: 7
  },
  input: {
    width: "80%",
    borderRadius: 5,
    paddingVertical: 8,
    paddingHorizontal: 16,
    borderColor: "#0278da",
    borderWidth: 1,
    color: "#0278da"
  },
  modalButtons: {
    marginTop: "10%",
    justifyContent: "space-between",
    width: "50%",
    flexDirection: "row"
  },
  addButton: {
    borderColor: "#38ba3c",
    borderWidth: 1,
    borderRadius: 8,
    paddingHorizontal: 10,
    paddingVertical: 5
  },
  addButtonText: {
    color: "#38ba3c"
  },
  cancelButton: {
    borderColor: "#e41515",
    borderWidth: 1,
    borderRadius: 8,
    paddingHorizontal: 10,
    paddingVertical: 5
  },
  cancelButtonText: {
    color: "#e41515"
  },
  showButton: {
    position: "absolute",
    right: 15,
    bottom: 15,
    backgroundColor: "#38ba3c",
    width: 50,
    height: 50,
    borderRadius: 50,
    alignItems: "center",
    justifyContent: "center"
  }
});

export default urlScreenStyles;
