const math = require("mathjs");
const pull = require("lodash.pull");
const data = require("./data.json");

function quadraticTask({ vectorC, vectorX, matrixA, matrixD, support, supportEx }) {
  const matrixAb = math.matrixFromColumns(...support.map((j) => math.column(matrixA, j)));
  const invAb = math.inv(matrixAb);
  const vectorCx = math.add(vectorC, math.multiply(vectorX, matrixD));
  const vectorCbX = support.map((j) => -vectorCx[j]);
  const vectorUx = math.multiply(vectorCbX, invAb);
  const deltaX = math.add(math.multiply(vectorUx, matrixA), vectorCx);

  const j0 = deltaX.findIndex((x) => x < 0 && !supportEx.includes(x));
  if (j0 === -1) return vectorX;

  const vectorL = math.zeros([vectorX.length]);
  vectorL[j0] = 1;

  const matrixDx = supportEx.map((j) => matrixD[j].filter((_, i) => supportEx.includes(i)));
  const matrixAx = math.matrixFromColumns(...supportEx.map((j) => math.column(matrixA, j)));
  const transposedAx = math.transpose(matrixAx);
  const topMatrix = math.concat(matrixDx, transposedAx);
  const dimension = matrixDx.length + matrixAx.length - transposedAx.length;
  const bottomMatrix = math.concat(matrixAx, math.zeros([dimension, dimension]));
  const matrixH = topMatrix.concat(bottomMatrix);

  const topPart = supportEx.map((j) => matrixD[j][j0]);
  const bottomPart = math.column(matrixA, j0).flat();
  const vectorBx = math.multiply(topPart.concat(bottomPart), -1);

  const res = math.multiply(math.inv(matrixH), vectorBx);
  supportEx.forEach((j) => (vectorL[j] = res[j]));

  const delta = math.multiply(math.multiply(vectorL, matrixD), vectorL);
  const tettaJ0 = !delta ? Infinity : math.abs(deltaX[j0]) / delta;

  const tettas = Array(vectorX.length).fill(Infinity);
  supportEx.forEach((j) => (tettas[j] = vectorL[j] < 0 ? -vectorX[j] / vectorL[j] : Infinity));
  tettas[j0] = tettaJ0;

  const q = math.min(tettas);
  if (q === Infinity) throw "Target function isn't limited";

  const jq = tettas.indexOf(q);
  const newVectorX = math.add(vectorX, math.multiply(vectorL, q));
  const diff = supportEx.filter((j) => !support.includes(j));

  if (j0 === jq) supportEx.push(jq);
  else if (diff.includes(jq)) pull(supportEx, jq);
  else {
    const s = support.indexOf(jq);
    const jp = diff.findIndex((j) => math.multiply(invAb, math.column(matrixA, j).flat())[s]);
    jp !== -1 ? pull(supportEx, jq) : (supportEx[s] = j0);
    support[s] = jp !== -1 ? jp : j0;
  }

  return quadraticTask({ vectorC, vectorX: newVectorX, matrixA, matrixD, support, supportEx });
}

const plan = quadraticTask(data);
console.log("Optimal plan: ", plan);
