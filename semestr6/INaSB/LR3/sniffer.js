const sniff = require("raw-socket-sniffer");
const { HOST } = require("./config.json");

sniff(HOST, (packet) => {
  const { payload } = packet;
  const output = { ...packet, payload: payload.toString("utf-8", 20) };
  console.log(output);
});
