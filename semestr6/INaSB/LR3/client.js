const { Socket } = require("net");
const { PORT, HOST } = require("./config.json");
const { createInterface } = require("readline");

const readline = createInterface({
  input: process.stdin,
  output: process.output
});

const client = new Socket();
client.connect(PORT, HOST, () => console.log("Client connected"));

readline.on("line", (input) => client.write(Buffer.from(input, "utf-8")));
