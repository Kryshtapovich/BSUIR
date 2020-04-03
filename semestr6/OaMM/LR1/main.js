const { multiply, diag, fraction } = require("mathjs");
const { matrix, vector, position } = require("./data.json");

function multiplyMatrices(matrixA, matrixB) {
  const len = matrixA.length;
  let res = [];
  for (let i = 0; i < len; i++) {
    res[i] = Array(len).fill(0);
    for(let j = 0; j < len; j++) {
      res[i][j] = matrixA[i][position] * matrixB[position][j];
      if(i !== position) {
        res[i][j] += matrixB[i][j]
      }
    }
  }
  return res;
}

function measureTime(matrixA, matrixB, callback, label) {
  console.time(label);
  const resultMatrix = callback(matrixA, matrixB).map((row) =>
    row.map((x) => {
      const { s, n, d } = fraction(x);
      return d === 1 ? `${s * n}` : `${s * n}/${d}`;
    })
  );
  console.timeLog(label);
  return resultMatrix;
}

const l = multiply(matrix, vector);
if (!l[position]) {
  console.log("matrix is not invertible");
} else {
  const number = l[position];
  l[position] = -1;

  const newVector = multiply(-1 / number, l);

  let identityMatrix = diag(Array(matrix.length).fill(1));
  newVector.forEach((x, i) => (identityMatrix[i][position] = x));

  const customMatrix = measureTime(identityMatrix, matrix, multiplyMatrices, "custom method");
  const libMatrix = measureTime(identityMatrix, matrix, multiply, "lib method");

  console.log("custom:", customMatrix);
  console.log("lib:", libMatrix);
}
