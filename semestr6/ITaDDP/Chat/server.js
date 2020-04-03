const { createSocket } = require("dgram");
const { PORT, HOST } = require("./config.json");

const server = createSocket("udp4");

const clients = [];
let pairs = {};

server.on("listening", () => {
  const { address, port } = server.address();
  console.log(`server listening ${address}:${port}`);
});

server.on("message", (data, { port }) => {
  const { header, text } = JSON.parse(data.toString("utf-8"));

  if (header === "connecting") {
    clients.push(port);
    if (clients.length % 2 === 0) {
      const [client1, client2] = clients.slice(-2);
      pairs = { ...pairs, [client1]: client2, [client2]: client1 };
    }
  } else if (header === "sending") {
    const recepient = pairs[port];
    recepient && server.send(text, recepient);
  }
});

server.bind(PORT, HOST);
