const { createServer } = require("net");
const { PORT, HOST } = require("./config.json");

createServer((socket) => {
  socket.on("data", (data) => console.log(data.toString("utf-8")));
}).listen(PORT, HOST);
