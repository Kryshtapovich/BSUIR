const math = require("mathjs");
const { simplex } = require("./simplex");
const data = require("./data.json");

function branchesBoundsMethod({ vectorC, matrixA, vectorB, vectorDNeg, vectorDPos }) {
  const [m, n] = math.size(matrixA);

  const indices = vectorC.reduce((acc, curr, i) => (curr > 0 ? [...acc, i] : acc), []);
  const vectorCExt = math.concat(vectorC, math.zeros([n + m]));
  indices.forEach((i) => {
    vectorCExt[i] *= -1;

    const tmp = vectorDPos[i] * -1;
    vectorDPos[i] = vectorDNeg[i] * -1;
    vectorDNeg[i] = tmp;

    matrixA = math.matrixFromColumns(
      ...Array.from({ length: m }, (_, j) =>
        math.multiply(math.column(matrixA, j), i === j ? -1 : 1)
      )
    );
  });

  const matrixBottomPart = math.diag(math.ones([n]));
  const matrixRightPart = math.diag(math.ones([n + m]));

  matrixA = math.concat(math.concat(matrixA, matrixBottomPart, 0), matrixRightPart);
  vectorB = math.concat(vectorB, vectorDPos);
  const vectorDNegExt = math.concat(vectorDNeg, math.zeros([n + m]));

  let xStar, r;
  const stack = [[0, vectorB, vectorDNegExt, [...vectorDNegExt]]];
  const basis = Array.from({ length: n + m }, (_, i) => n + i);

  while (stack.length) {
    const [alpha, vectorB, vectorD, delta] = stack.pop();

    const newAlpha = alpha + math.multiply(vectorCExt, vectorD);
    const beta = math.subtract(vectorB, math.multiply(matrixA, vectorD));

    const optimalPlan = simplex(matrixA, beta, vectorCExt, basis);

    const item = optimalPlan.slice(0, n).find((x, i) => !Number.isInteger(x) && !basis.includes(i));

    if (item) {
      const value = math.multiply(vectorCExt, optimalPlan) + newAlpha;

      if (!xStar || r < Math.floor(value)) {
        const index = optimalPlan.indexOf(item);
        const zeros = math.zeros([2 * n + m]);

        const newVectorB = beta.map((x, i) => (i === m + index - 1 ? Math.floor(item) : x));
        stack.push([newAlpha, newVectorB, zeros, delta]);

        zeros[index] = Math.ceil(item);
        stack.push([newAlpha, beta, zeros, math.add(delta, zeros)]);
      }
    } else {
      const plan = math.add(optimalPlan, delta);
      const value = math.multiply(vectorCExt, plan) + newAlpha;

      if (!xStar || r < value) {
        xStar = plan;
        r = value;
      }
    }
  }

  if (!xStar) throw "Task is not compatible";

  return {
    r,
    xStar: xStar.filter((_, i) => vectorCExt[i] !== 0).map((x, i) => (vectorC[i] > 0 ? -x : x))
  };
}

console.log(branchesBoundsMethod(data));
