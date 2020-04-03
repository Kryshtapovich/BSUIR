const { invertMatrix } = require("./lib");
const math = require("mathjs");
const { vectorC, matrixA, vectorX, vectorB } = require("./data.json");

function mainSimplexPhase(vectorC, matrixA, vectorX, vectorB) {
  let replaceIndex;

  for (let i = 0; ; i++) {
    const basisMatrix = math.matrixFromColumns(...vectorB.map((j) => math.column(matrixA, j - 1).flat()));
    
    const invMatrix = i ? invertMatrix(basisMatrix, vectorB, replaceIndex) : math.inv(basisMatrix);

    const vectorCB = vectorB.map((j) => vectorC[j - 1]);

    const potentialVector = math.multiply(vectorCB, invMatrix);

    const gradeVector = math.subtract(math.multiply(potentialVector, matrixA), vectorC);

    const j0 = gradeVector.findIndex((x, j) => !vectorB.includes(j + 1) && x < 0);
    if (j0 === -1) return vectorX;

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

try {
  const optimalPLan = mainSimplexPhase(vectorC, matrixA, vectorX, vectorB);
  console.log("Optimal plan:", optimalPLan);
} catch (error) {
  console.log("Optimal plan doesn't exist", error);
}
