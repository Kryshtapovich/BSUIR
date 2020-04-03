const { multiply, diag } = require("mathjs");

function multiplyMatrices(matrixA, matrixB, position) {
  const len = matrixA.length;
  const res = [];
  for (let i = 0; i < len; i++) {
    res[i] = Array(len).fill(0);
    for (let j = 0; j < len; j++) {
      res[i][j] = matrixA[i][position] * matrixB[position][j];
      if (i !== position) res[i][j] += matrixB[i][j];
    }
  }
  return res;
}

function invertMatrix(matrix, vector, position) {
  const l = multiply(matrix, vector);

  if (!l[position]) {
    throw "Matrix is not invertible";
  } else {
    const number = l[position];
    l[position] = -1;

    const newVector = multiply(-1 / number, l);

    const identityMatrix = diag(Array(matrix.length).fill(1));
    newVector.forEach((x, i) => (identityMatrix[i][position] = x));

    return multiplyMatrices(identityMatrix, matrix, position);
  }
}

module.exports = { invertMatrix };
