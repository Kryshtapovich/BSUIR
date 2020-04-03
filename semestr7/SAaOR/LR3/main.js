const { source, sink, graph } = require("./data.json");

function bfs(graph, source, sink, path) {
  const visited = new Array(graph.length).fill(false);

  const queue = [source];
  visited[source] = true;
  path[source] = -1;

  while (queue.length) {
    const i = queue.shift();

    for (let j = 0; j < graph.length; j++) {
      if (!visited[j] && graph[i][j] !== 0) {
        path[j] = i;
        if (j === sink) return true;
        else {
          queue.push(j);
          visited[j] = true;
        }
      }
    }
  }

  return false;
}

function fordFulkerson(graph, source, sink) {
  const residualGraph = graph.map((x) => x.slice());
  const path = new Array(graph.length);

  let maxFlow = 0;
  const pathes = [];

  while (bfs(residualGraph, source, sink, path)) {
    let tetta = Infinity;
    const reversedPath = [];

    for (let j = sink; j !== source; j = path[j]) {
      const i = path[j];
      reversedPath.push(`(${i}, ${j})`);
      tetta = Math.min(tetta, residualGraph[i][j]);
      residualGraph[i][j] -= tetta;
      residualGraph[j][i] += tetta;
    }

    pathes.push({ path: reversedPath.reverse().join(" -> "), flow: tetta });
    maxFlow += tetta;
  }

  return { maxFlow, pathes };
}

const { maxFlow, pathes } = fordFulkerson(graph, source, sink);
console.log("Maximum flow:", maxFlow);
console.log("Pathes:", pathes);
