import { makeAutoObservable, reaction } from "mobx";

export default class CalculatorStore {
  buffer: string = "0";
  firstValue: number = 0;
  secondValue: number = 0;
  result: string = "0";
  operation: string = "";
  isProcessing: boolean = false;

  constructor() {
    makeAutoObservable(this);
    reaction(
      () => this.firstValue,
      () => {
        this.result = this.firstValue.toString();
      }
    );
  }

  input = (symbol: string) => {
    if (this.buffer.includes(".") && symbol === ".") {
      return;
    }
    this.buffer += symbol;
    this.firstValue = parseFloat(this.buffer);
  };

  clear = () => {
    this.isProcessing = false;
    this.secondValue = 0;
    this.firstValue = 0;
    this.operation = "";
    this.buffer = "";
    this.result = "0";
  };

  backspace = () => {
    this.buffer = this.buffer.slice(0, -1);
    this.firstValue = this.buffer === "" ? 0 : parseFloat(this.buffer);
  };

  textResult = (length?: number) => {
    if(this.buffer.slice(-1) === ".") {
      return this.buffer;
    }
    return this.result.slice(0, length);
  };

  switchState = () => {
    this.secondValue = this.firstValue;
    this.firstValue = 0;
    this.buffer = "";
  };

  binOperation = (operation: string) => {
    if (!this.isProcessing) {
      this.isProcessing = true;
      this.switchState();
      this.operation = operation;
    }
  };

  equal = () => {
    switch (this.operation) {
      case "+":
        this.firstValue += this.secondValue;
        break;
      case "-":
        this.firstValue = this.secondValue - this.firstValue;
        break;
      case "×":
        this.firstValue = this.secondValue * this.firstValue;
        break;
      case "÷":
        this.firstValue = this.secondValue / this.firstValue;
        break;
      case "x":
        this.firstValue = this.secondValue ** this.firstValue;
        break;
      case "\u{221A}":
        this.firstValue = this.secondValue ** (1 / this.firstValue);
        break;
    }
    this.isProcessing = false;
    this.buffer = this.firstValue.toString();
    this.operation = "";
  };

  factorial = () => {
    if (this.firstValue > 170) {
      this.firstValue = Number.POSITIVE_INFINITY;
    } else if (!Number.isInteger(this.firstValue) || this.firstValue < 0) {
      this.buffer = "ERROR";
    } else {
      let res = 1;
      for (let i = 1; i <= this.firstValue; i++) {
        res *= i;
      }
      this.firstValue = res;
    }
  };

  negative = () => {
    this.firstValue *= -1;
    this.equal();
  };

  sin = () => {
    this.firstValue = Math.sin(this.firstValue);
    this.equal();
  };

  cos = () => {
    this.firstValue = Math.cos(this.firstValue);
    this.equal();
  };

  tan = () => {
    this.firstValue = Math.tan(this.firstValue);
    this.equal();
  };

  asin = () => {
    this.firstValue = Math.asin(this.firstValue);
    this.equal();
  };

  acos = () => {
    this.firstValue = Math.acos(this.firstValue);
    this.equal();
  };

  atan = () => {
    this.firstValue = Math.atan(this.firstValue);
    this.equal();
  };

  ln = () => {
    this.firstValue = Math.log(this.firstValue);
    this.equal();
  };

  lg = () => {
    this.firstValue = Math.log10(this.firstValue);
    this.equal();
  };

  exp = () => {
    this.firstValue = Math.E;
    this.equal();
  };

  pi = () => {
    this.firstValue = Math.PI;
    this.equal();
  };

  rand = () => {
    this.firstValue = Math.random();
    this.equal();
  };
}
