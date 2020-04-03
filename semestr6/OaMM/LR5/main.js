const { zeros, lusolve, min } = require("mathjs");
const { remove, groupBy, isEqual, cloneDeep } = require("lodash");
const { vectorA, vectorB, matrixC } = require("./data.json");

const [m, n] = [vectorA.length, vectorB.length];

const cells = zeros([m, n])
  .map((row, i) => row.map((_, j) => ({ i, j })))
  .flat();

function firstPhase(vectorA, vectorB) {
  const basis = [];
  const matrix = zeros([m, n]);

  for (let i = 0, j = 0; i < m && j < n; ) {
    const value = min(vectorA[i], vectorB[j]);

    vectorA[i] -= value;
    vectorB[j] -= value;
    matrix[i][j] = value;

    basis.push({ i, j });

    if (!vectorA[i]) i++;
    else if (!vectorB[j]) j++;

    if (i === m) for (i--, j++; j < n; j++) basis.push({ i, j });
    if (j === n) for (i++, j--; i < m; i++) basis.push({ i, j });
  }

  return { matrix, basis };
}

function clearBasis(basis, key) {
  Object.values(groupBy(basis, key))
    .filter((arr) => arr.length === 1)
    .forEach((arr) => remove(basis, (cell) => isEqual(cell, arr[0])));
}

function polarizeBasis(basis, cell, sign = true) {
  if (cell && !cell.sign) cell.sign = sign;
  else return basis;
  const rowCell = basis.find(({ i, j }) => i === cell.i && j !== cell.j);
  const columnCell = basis.find(({ i, j }) => i !== cell.i && j === cell.j);
  polarizeBasis(basis, rowCell, !sign);
  return polarizeBasis(basis, columnCell, !sign);
}

function secondPhase(matrixC, matrix, basis) {
  const b = zeros([m + n]);
  const matrixUV = zeros([m + n, m + n]);
  basis.forEach(({ i, j }, index) => {
    b[index] = matrixC[i][j];
    matrixUV[index][i] = 1;
    matrixUV[index][j + m] = 1;
  });
  matrixUV[n + m - 1][0] = 1;

  const solution = lusolve(matrixUV, b).flat();
  const u = solution.slice(0, m);
  const v = solution.slice(m);

  const notBasis = cells.filter((x) => !basis.find((y) => isEqual(x, y)));

  const cell = notBasis.find(({ i, j }) => u[i] + v[j] > matrixC[i][j]);
  if (!cell) return matrix;
  basis.push(cell);

  const basisCopy = cloneDeep(basis);
  clearBasis(basisCopy, "i");
  clearBasis(basisCopy, "j");
  const polarizedBasis = polarizeBasis(basisCopy, cloneDeep(cell));

  const tetta = min(polarizedBasis.map(({ i, j, sign }) => (!sign ? matrix[i][j] : Infinity)));
  polarizedBasis.forEach(({ i, j, sign }) => (matrix[i][j] += sign ? tetta : -tetta));

  for (const { i, j, sign } of polarizedBasis) {
    if (!matrix[i][j] && !sign) {
      remove(basis, (cell) => isEqual(cell, { i, j }));
      break;
    }
  }

  return secondPhase(matrixC, matrix, basis);
}

const { matrix, basis } = firstPhase(vectorA, vectorB);

const plan = secondPhase(matrixC, matrix, basis);
console.log("Optimal plan:", plan);
