const { start, finish, graph } = require("./data.json");

function STPath(s, t, graph) {
  let stack = [];

  const dfs = (apex) => {
    apex.color = "gray";
    graph.forEach((x) => x.color === "white" && dfs(x));
    stack.push(apex);
  };

  dfs(graph[s]);

  stack = stack.map(({ color, ...rest }) => rest).reverse();

  const startIndex = stack.findIndex(({ source }) => source === s);
  const finishIndex = stack.findIndex(({ dest }) => dest === t);

  if (startIndex > finishIndex) throw "No way";

  const sortedSources = [...new Set(stack.map(({ source }) => source))];
  const opt = Array(sortedSources.length).fill(-Infinity);
  const x = Array(sortedSources.length).fill(0);
  opt[s] = 0;
  x[s] = undefined;

  sortedSources.forEach((apex) => {
    stack
      .filter(({ dest }) => dest === apex)
      .forEach(({ source, weight }) => {
        const cur = sortedSources[source];
        if (weight + opt[cur] > opt[apex]) {
          opt[apex] = weight + opt[cur];
          x[apex] = source;
        }
      });
  });

  return { opt, x };
}

console.log(STPath(start, finish, graph));
