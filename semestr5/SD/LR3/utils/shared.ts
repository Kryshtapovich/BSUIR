import { Theme } from "@react-navigation/native";
import { LinearGradientProps } from "expo-linear-gradient";

export const theme: Theme = {
  colors: {
    background: "white"
  }
} as any;

export const mainGradient: LinearGradientProps = {
  colors: ["#ee0d74", "#ff6606"],
  start: { x: 0, y: 0.5 },
  end: { x: 1, y: 1 }
};

export const buttonGradient: LinearGradientProps = {
  colors: ["#3ae3b8", "#cedf59"],
  start: { x: 0, y: 0.5 },
  end: { x: 1, y: 1 }
};
