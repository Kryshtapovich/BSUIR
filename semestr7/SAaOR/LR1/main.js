const math = require("mathjs");
const { simplex } = require("./simplex");
const data = require("./data.json");

function fractionPart(number) {
  return number - Math.floor(number);
}

function clippingPlaneMethod({ matrixA, vectorB }) {
  const [vectorX, dirtBasis] = simplex(matrixA, vectorB);

  if (vectorX.every(Number.isInteger)) return vectorX;

  const basis = dirtBasis.map((x) => x - 1);
  const notBasis = Object.keys(vectorX)
    .map(Number)
    .filter((i) => !basis.includes(i));

  const matrixAb = math.matrixFromColumns(...basis.map((i) => math.column(matrixA, i).flat()));
  const matrixAn = math.matrixFromColumns(...notBasis.map((i) => math.column(matrixA, i).flat()));
  const matrixProduct = math.multiply(math.inv(matrixAb), matrixAn);

  const k = basis[vectorX.findIndex((x) => !Number.isInteger(x))];
  const fractions = matrixProduct[k].map(fractionPart);

  return Array.from({ length: vectorX.length }, (_, i) => fractions[notBasis.indexOf(i)] || 0)
    .concat(-1)
    .concat(fractionPart(vectorX[k]));
}

console.log(clippingPlaneMethod(data));
