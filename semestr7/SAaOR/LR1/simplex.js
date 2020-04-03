const math = require("mathjs");

const basis = [0];

function mainPhase(matrixA, vectorB, vectorC, vectorX) {
  const basisMatrix = math.matrixFromColumns(
    ...vectorB.map((j) => math.column(matrixA, j - 1).flat())
  );

  const invMatrix = math.inv(basisMatrix);

  const vectorCB = vectorB.map((j) => vectorC[j - 1]);

  const potentialVector = math.multiply(vectorCB, invMatrix);

  const gradeVector = math.subtract(math.multiply(potentialVector, matrixA), vectorC);

  const j0 = gradeVector.findIndex((x, j) => !vectorB.includes(j + 1) && x < 0);
  if (j0 === -1) return [vectorX, vectorB];

  const vectorZ = math.multiply(invMatrix, math.column(matrixA, j0).flat());

  const vectorT = vectorZ.map((z, i) => (z > 0 ? vectorX[vectorB[i] - 1] / z : Infinity));

  const tetta = math.min(vectorT);
  if (tetta === Infinity) throw "Target function has no limits";
  const replaceIndex = vectorT.indexOf(tetta);

  vectorB.forEach((j, i) => (vectorX[j - 1] -= tetta * vectorZ[i]));
  vectorB[replaceIndex] = j0 + 1;
  vectorX[j0] = tetta;

  return mainPhase(matrixA, vectorB, vectorC, vectorX);
}

function simplex(matrixA, vectorB) {
  const [m, n] = math.size(matrixA);

  vectorB = vectorB.map((j, i) => {
    if (j < 0) matrixA[i] = math.multiply(matrixA[i], -1);
    return math.abs(j);
  });

  const [zeros, ones] = [math.zeros([n]), math.ones([m])];

  const newMatrix = math.concat(matrixA, math.diag(ones));

  const vectorJb = ones.map((z, i) => n + i + z);

  const vectorC = [...zeros, ...ones.map((x) => -x)];

  const vectorX = [...zeros, ...vectorB];

  const [resX, resB] = mainPhase(newMatrix, vectorJb, vectorC, vectorX);

  if (resX.slice(n).some((x) => x !== 0)) throw "Task is not compatible";

  const k = resB.map((j) => j - n).reduce((_, j, i) => j > 0 && i);

  const vectorJnb = [...Array(n - basis.length + 1).keys()].filter((x) => !basis.includes(x));

  const invAb = math.inv(
    math.matrixFromColumns(...resB.map((j) => math.column(newMatrix, j - 1).flat()))
  );

  const vectorL = vectorJnb.map((j) => math.multiply(invAb, math.column(newMatrix, j).flat()));

  if (vectorL.every((x) => x[k] === 0)) {
    vectorJb.splice(k, 1);
  }

  return [resX.slice(0, n), vectorJb];
}

module.exports = { simplex };
