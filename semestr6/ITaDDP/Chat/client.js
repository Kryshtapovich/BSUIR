const { createSocket } = require("dgram");
const { createInterface } = require("readline");
const { PORT, HOST } = require("./config.json");

const client = createSocket("udp4");
let user = null;

const readline = createInterface({
  input: process.stdin,
  output: process.stdout
});

client.on("message", (msg) => console.log(msg.toString("utf-8")));

readline.question("Enter username: ", (username) => {
  user = username;
  const messageObj = { header: "connecting" };
  const message = Buffer.from(JSON.stringify(messageObj), "utf-8");
  client.send(message, PORT, HOST);
});

readline.on("line", (input) => {
  const messageObj = { header: "sending", text: `${user}: ${input}` };
  const message = Buffer.from(JSON.stringify(messageObj), "utf-8");
  client.send(message, PORT, HOST);
  console.log(`you: ${input}`);
});
