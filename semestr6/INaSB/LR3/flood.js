const { Socket } = require("net");
const { PORT, HOST } = require("./config.json");

function createFlooder() {
  const flooder = new Socket();
  flooder.connect(PORT, HOST, () => console.log("Flooder created"));
  setInterval(() => flooder.write(Buffer.from(String(Date.now()), "utf-8")), 1000);
}

setInterval(createFlooder, 1000);
