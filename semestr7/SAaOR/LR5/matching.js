function maximumMatching(graph) {
  const matching = new Array(graph.length).fill(-1);
  let visited = new Array(graph.length);

  const dfs = (j) => {
    for (let i = 0; i < graph.length; i++) {
      if (graph[j][i] === 1 && !visited[i]) {
        visited[i] = true;

        if (matching[i] === -1 || dfs(matching[i])) {
          matching[i] = j;
          return true;
        }
      }
    }

    return false;
  };

  graph.forEach((_, i) => {
    visited = visited.fill(false);
    dfs(i);
  });

  return matching.map((i, j) => [i, j]).filter((v) => !v.includes(-1));
}

module.exports = { maximumMatching };
