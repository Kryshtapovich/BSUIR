const { caesar, vigenere } = require("./lib");
const { caesarData, vigenereData } = require("./data.json");

const caesarResult = caesar(caesarData.key, caesarData.text, caesarData.operation);
console.log("caesar input:", caesarData);
console.log("caesar output:", caesarResult);

const vigenereResult = vigenere(vigenereData.key, vigenereData.text, vigenereData.operation);
console.log("vigenere input:", vigenereData);
console.log("vigenere output:", vigenereResult);
