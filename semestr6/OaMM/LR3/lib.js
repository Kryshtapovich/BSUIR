const math = require("mathjs");

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
  const l = math.multiply(matrix, vector);

  if (!l[position]) {
    throw "Matrix is not invertible";
  } else {
    const number = l[position];
    l[position] = -1;

    const newVector = math.multiply(-1 / number, l);

    const identityMatrix = math.diag(Array(matrix.length).fill(1));
    newVector.forEach((x, i) => (identityMatrix[i][position] = x));

    return multiplyMatrices(identityMatrix, matrix, position);
  }
}

function mainPhase(matrixA, vectorB, vectorC, vectorX) {
  let replaceIndex;

  for (let i = 0; ; i++) {
    const basisMatrix = math.matrixFromColumns(
      ...vectorB.map((j) => math.column(matrixA, j - 1).flat())
    );

    const invMatrix = i ? invertMatrix(basisMatrix, vectorB, replaceIndex) : math.inv(basisMatrix);

    const vectorCB = vectorB.map((j) => vectorC[j - 1]);

    const potentialVector = math.multiply(vectorCB, invMatrix);

    const gradeVector = math.subtract(math.multiply(potentialVector, matrixA), vectorC);

    const j0 = gradeVector.findIndex((x, j) => !vectorB.includes(j + 1) && x < 0);
    if (j0 === -1) return [vectorX, vectorB];

    const vectorZ = math.multiply(invMatrix, math.column(matrixA, j0).flat());

    const vectorT = vectorZ.map((z, i) => (z > 0 ? vectorX[vectorB[i] - 1] / z : Infinity));

    const tetta = math.min(vectorT);
    if (tetta === Infinity) throw "Target function has no limits";
    replaceIndex = vectorT.indexOf(tetta);

    vectorB.forEach((j, i) => (vectorX[j - 1] -= tetta * vectorZ[i]));
    vectorB[replaceIndex] = j0 + 1;
    vectorX[j0] = tetta;
  }
}

module.exports = { mainPhase };
