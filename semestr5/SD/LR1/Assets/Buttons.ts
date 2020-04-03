import { StyleProp, TextStyle, ViewStyle } from "react-native";

import { store } from "../Stores";

const { calculatorStore, themeStore } = store;

export interface ButtonModel {
  title: string;
  superScript?: string;
  buttonStyle?: StyleProp<ViewStyle>;
  textStyle?: StyleProp<TextStyle>;
  canLongPress?: boolean;
  isSticky?: boolean;
  onPress: (arg?: any) => void;
}

export const usualButtons: Array<Array<ButtonModel>> = [
  [
    { title: "AC", onPress: calculatorStore.clear },
    { title: "C", onPress: calculatorStore.backspace, canLongPress: true },
    { title: "+/-", onPress: calculatorStore.negative },
    { title: "÷", onPress: () => calculatorStore.binOperation("÷"), isSticky: true }
  ],
  [
    { title: "7", onPress: () => calculatorStore.input("7") },
    { title: "8", onPress: () => calculatorStore.input("8") },
    { title: "9", onPress: () => calculatorStore.input("9") },
    { title: "×", onPress: () => calculatorStore.binOperation("×"), isSticky: true }
  ],
  [
    { title: "4", onPress: () => calculatorStore.input("4") },
    { title: "5", onPress: () => calculatorStore.input("5") },
    { title: "6", onPress: () => calculatorStore.input("6") },
    { title: "-", onPress: () => calculatorStore.binOperation("-"), isSticky: true }
  ],
  [
    { title: "1", onPress: () => calculatorStore.input("1") },
    { title: "2", onPress: () => calculatorStore.input("2") },
    { title: "3", onPress: () => calculatorStore.input("3") },
    { title: "+", onPress: () => calculatorStore.binOperation("+"), isSticky: true }
  ],
  [
    { title: "0", onPress: () => calculatorStore.input("0"), buttonStyle: { width: "47%" } },
    { title: ".", onPress: () => calculatorStore.input(".") },
    { title: "=", onPress: calculatorStore.equal }
  ]
];

export const scientificButtons: Array<Array<ButtonModel>> = [
  [
    { title: "", onPress: themeStore.toggle, textStyle: { fontSize: 38 } },
    {
      title: "x",
      onPress: () => calculatorStore.binOperation("x"),
      superScript: "y",
      isSticky: true
    },
    { title: "\u{221A}", onPress: () => calculatorStore.binOperation("\u{221A}"), isSticky: true }
  ],
  [
    { title: "ln", onPress: calculatorStore.ln },
    { title: "lg", onPress: calculatorStore.lg },
    { title: "x!", onPress: calculatorStore.factorial }
  ],
  [
    { title: "sin", onPress: calculatorStore.sin },
    { title: "cos", onPress: calculatorStore.cos },
    { title: "tan", onPress: calculatorStore.tan }
  ],
  [
    { title: "sin", onPress: calculatorStore.asin, superScript: "-1" },
    { title: "cos", onPress: calculatorStore.acos, superScript: "-1" },
    { title: "tan", onPress: calculatorStore.atan, superScript: "-1" }
  ],
  [
    { title: "e", onPress: calculatorStore.exp },
    { title: "π", onPress: calculatorStore.pi },
    { title: "Rand", onPress: calculatorStore.rand }
  ]
];
