class MagnitudePacketParser {
  constructor(reporter) {
    this.header = "AD: ";
    this.reporter = reporter;
    this.data = "";
  }

  matchesHeader(buffer) {
    return buffer === this.header;
  }

  report() {
    //console.log(`Reporting data: ${this.data}`)
    this.reporter(parseInt("0x" + this.data));
  }

  parse(byte) {
    //console.log(`Parse mag: ${String.fromCharCode(byte)}`)
    this.data = this.data.concat(String.fromCharCode(byte));
    //console.log(`Parsing Mag. Data: ${this.data}`);
    if (this.data.length === 4){
      this.report();
      this.data = "";
      return true;
    }
    return false;
  }
}


export function RadarParser(callback) {

  let buffer = "    ";
  let mode = 'match';
  let parser = null;
  let parsers = [
    new MagnitudePacketParser(callback)
  ];

  
  function lookForMatch(byte) {
    buffer = buffer.substr(1).concat(String.fromCharCode(byte));
    //console.log(`LookForMatch, buffer: ${buffer}`)
    let match = parsers.find(parser => parser.matchesHeader(buffer));
    
    if (match) {
      mode = 'parse';
      parser = match;
    }
  }

  function parseByte(byte) {
    if (parser.parse(byte))
    {
      mode = 'match';
      buffer = "    ";
    }
  }

  return async function parse(bytes) {
    //console.log("Parse:", bytes);
    bytes.forEach(byte => {
      switch(mode) {
        case "match":
          lookForMatch(byte);
          break;

        case "parse":
          parseByte(byte);
          break;
      }
    });

    return;
  }
}
