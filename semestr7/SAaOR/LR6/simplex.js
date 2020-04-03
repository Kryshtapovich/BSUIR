const math = require("mathjs");

function simplex(matrixA, vectorB, vectorC, basis) {
  const matrixAb = math.matrixFromColumns(...basis.map((j) => math.column(matrixA, j).flat()));

  const invMatrix = math.inv(matrixAb);

  const vectorCb = basis.map((j) => vectorC[j]);

  const vectorY = math.multiply(vectorCb, invMatrix);

  const kappaB = math.multiply(invMatrix, vectorB);

  const kappa = Array(vectorC.length).fill(0);

  basis.forEach((j, i) => (kappa[j] = kappaB[i]));

  if (kappa.every((k) => k >= 0)) return kappa;

  const index = basis.findIndex((j) => j === kappa.findIndex((k) => k < 0));

  const deltaY = invMatrix[0];

  const notBasis = [...Array(vectorC.length).keys()].filter((j) => !basis.includes(j));

  const mu = notBasis.map((j) => math.multiply(deltaY, math.column(matrixA, j).flat()));

  if (mu.every((m) => m >= 0)) throw "Task is not comapatible";

  const sigma = notBasis.map(
    (j, i) => (vectorC[i] - math.multiply(math.column(matrixA, j).flat(), vectorY)) / mu[i]
  );

  const newComp = sigma.findIndex((s) => s === math.min(sigma));

  const newBasis = [...basis];
  newBasis[index] = newComp;

  return simplex(matrixA, vectorB, vectorC, newBasis);
}

module.exports = { simplex };
