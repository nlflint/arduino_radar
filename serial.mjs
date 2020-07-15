import SerialPort from 'serialport';
import ByteLength from '@serialport/parser-byte-length';
import readline from "readline";
import {RadarParser} from "./radar.mjs";

const port = new SerialPort('/dev/ttyUSB0', {
    baudRate: 512000,
    dataBits: 8,
    stopBits: 1,
    parity: "none"
  })

readline.emitKeypressEvents(process.stdin);
process.stdin.setRawMode(true);

const parser = port.pipe(new ByteLength({length: 1}))
parser.on('data', RadarParser((mag) => console.log(`Mag: ${mag}`)));


process.stdin.on('keypress', (str, key) => {
  process.stdout.write(str + '\n');
  
  let commands = {
    "q": process.exit,
    "Q": process.exit,
    "d": debugModeOn,
    "f": debugModeOff,


  };
  
  if (commands.hasOwnProperty(str)) {
    commands[str]();
  }
  else {
    process.stdout.write("Unknown command!");
  }
  
  
  prompt();
});

function prompt() {
  process.stdout.write("\n?>");
}

function printHelp() {
  console.log("\nv: get version");
  console.log("2: exit config mode");
  console.log("q: quit");
}

function debugModeOn() {
  process.stdout.write("Entering config mode");
  port.write([0x41,0x54,0x2b,0x44,0x45,0x42,0x55,0x47,0x3d,0x30,0x30,0x30,0x32]);
}

function debugModeOff() {
  process.stdout.write("Entering config mode");
  port.write([0x41,0x54,0x2b,0x44,0x45,0x42,0x55,0x47,0x3d,0x30,0x30,0x30,0x30]);
}

prompt();