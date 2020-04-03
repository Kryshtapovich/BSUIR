const math = require("mathjs");
const { mainPhase } = require("./lib");
const { basis, matrixA, vectorB } = require("./data.json");

function simplexStart(matrixA, vectorB) {
  const [m, n] = math.size(matrixA);

  vectorB = vectorB.map((j, i) => {
    if (j < 0) matrixA[i] = math.multiply(matrixA[i], -1);
    return math.abs(j);
  });

  const [zeros, ones] = [math.zeros([n]), math.ones([m])];

  let newMatrix = math.concat(matrixA, math.diag(ones));

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
    matrixA.splice(k, 1);
    vectorB.splice(k, 1);
    vectorC.splice(n + k, 1);
    vectorJb.splice(k, 1);
    newMatrix = newMatrix.map((row) => row.filter((_, i) => i !== k));
  }

  return [resX.slice(0, n), vectorJb];
}

const [x, b] = simplexStart(matrixA, vectorB);

console.log("vector x:", x);
console.log("vector B:", b);
