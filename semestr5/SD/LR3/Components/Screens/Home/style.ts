import { StyleSheet } from "react-native";

const defaultStyle = StyleSheet.create({
  navbar: {
    width: "100%",
    marginTop: 15,
    zIndex: 1,
    flexDirection: "column"
  },
  navbarHeader: {
    paddingHorizontal: 10,
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between"
  },
  title: {
    fontSize: 30,
    fontWeight: "800",
    alignSelf: "center",
    color: "#f7393e"
  },
  version: {
    fontSize: 14,
    color: "#f7393e"
  },
  searchWrapper: {
    marginTop: 5,
    alignSelf: "center"
  },
  searchInput: {
    color: "#a93567"
  },
  notes: {
    alignSelf: "center"
  },
  addButton: {
    position: "absolute",
    right: 15,
    bottom: 15,
    width: 50,
    height: 50
  }
});

export const portraitStyle = StyleSheet.create({
  ...defaultStyle,
  navbar: {
    ...defaultStyle.navbar,
    marginBottom: "5%"
  },
  search: {
    ...defaultStyle.searchWrapper,
    width: "93%"
  },
  notes: {
    ...defaultStyle.notes,
    width: "96%",
    flexDirection: "column"
  }
});

export const landscapeStyle = StyleSheet.create({
  ...defaultStyle,
  navbar: {
    ...defaultStyle.navbar,
    marginBottom: "3%"
  },
  search: {
    ...defaultStyle.searchWrapper,
    width: "96%"
  },
  notes: {
    ...defaultStyle.notes,
    width: "98%",
    flexDirection: "row",
    flexWrap: "wrap"
  }
});
