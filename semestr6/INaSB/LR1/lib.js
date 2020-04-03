const operations = {
  decrypt: 0,
  encrypt: 1
};

const letters = "abcdefghijklmnopqrstuvwxyz";
const length = 26;

function caesar(key, text, operation) {
  let result = "";
  const isEncrypting = operations[operation];

  for (const symbol of text) {
    let code = letters.indexOf(symbol);
    code = isEncrypting ? (code + key) % length : (code - key + length) % length;
    result += letters[code];
  }
  return result;
}

function vigenere(key, text, operation) {
  const square = letters
    .split("")
    .map((_, i) => caesar(length - i, letters, operations.encrypt).split(""));
  const word = text.split("");
  const keyWord =
    key.length < text.length ? word.map((_, i) => key[i % key.length]) : key.split("");

  let result = "";
  const isEncrypting = operations[operation];

  keyWord.forEach((symbol, i) => {
    const row = letters.indexOf(symbol);
    const column = square[isEncrypting ? 0 : row].indexOf(word[i]);
    result += square[isEncrypting ? row : 0][column];
  });
  return result;
}

module.exports = { caesar, vigenere };
