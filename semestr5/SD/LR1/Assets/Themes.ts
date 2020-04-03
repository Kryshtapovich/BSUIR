export interface Theme {
  background: string;
  color: string;
  androidBorder: string;
}

export const lightTheme: Theme = {
  background: "white",
  color: "#B026FF",
  androidBorder: "rgba(176, 38, 255, .3)"
};

export const darkTheme: Theme = {
  background: "black",
  color: "#00ffbf",
  androidBorder: "rgba(0, 255, 191, .4)"
};
