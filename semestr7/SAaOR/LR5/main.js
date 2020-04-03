const math = require("mathjs");
const { matrixC } = require("./data.json");
const { maximumMatching } = require("./matching");

function assignmentTask(matrix) {
  const { length } = matrix;
  const alphas = math.zeros([length]);
  const betas = matrix.map((_, i) => math.min(math.column(matrix, i).flat()));

  const iteration = (alphas, betas) => {
    const graph = math.zeros([length, length]);
    for (let i = 0; i < length; i++) {
      for (let j = 0; j < length; j++) {
        if (alphas[i] + betas[j] === matrix[i][j]) {
          graph[i][j] = 1;
        }
      }
    }

    const matching = maximumMatching(graph);

    if (matching.length === length) return matching;

    const orientedGraph = graph.map((row) => row.slice());

    for (let i = 0; i < length; i++) {
      for (let j = 0; j < length; j++) {
        const apex = matching.find((x) => x[0] === i && x[1] === j);
        if (apex) orientedGraph[i][j] *= -1;
      }
    }

    const stars = orientedGraph.map((row) => {
      if (row.includes(-1)) return null;
      return row.map((x, i) => (x === 1 ? i : null)).filter(Boolean);
    });

    const upperPart = stars.reduce((acc, curr, i) => (curr ? [...acc, i] : acc), []);
    const bottomPart = stars.filter(Boolean).flat();

    const tmpAlphas = Array.from({ length }, (_, i) => (upperPart.includes(i) ? 1 : -1));
    const tmpBetas = Array.from({ length }, (_, i) => (bottomPart.includes(i) ? -1 : 1));

    const tettas = [];
    for (let i = 0; i < length; i++) {
      for (let j = 0; j < length; j++) {
        if (upperPart.includes(i) && !bottomPart.includes(j)) {
          tettas.push((matrix[i][j] - alphas[i] - betas[j]) / 2);
        }
      }
    }

    const tetta = math.min(tettas);
    const newAlphas = alphas.map((x, i) => x + tetta * tmpAlphas[i]);
    const newBetas = betas.map((x, i) => x + tetta * tmpBetas[i]);

    return iteration(newAlphas, newBetas);
  };

  return iteration(alphas, betas);
}

const matching = assignmentTask(matrixC);
console.log("Assignment:", matching);
