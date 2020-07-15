#define rxPin 3
#define txPin 4
#define led 13
#define AWAITING_FRAME_HEADERS 0
#define PARSE_MODE 1
#define FRAME_HEADER 0x59
#define DISTANCE_PACKET_LENGTH 7
#define CHECKSUM_INDEX 6
#define NOTHING -1
#define DISTANCES_LENGTH 30

char currentMode;
char lastReceivedCharacter;
char distancePacket[DISTANCE_PACKET_LENGTH];
char currentPacketPosition = 0;
int distances[DISTANCES_LENGTH] = {0};
char nextDistance = 0;

void setup()  {

  //OSCCAL = 154;
  
  // define pin modes for tx, rx:
//  pinMode(rxPin, INPUT);
//  pinMode(txPin, OUTPUT);
  pinMode(led, OUTPUT);
  
  // set the data rate for the SoftwareSerial port
  Serial.begin(115200);

  lastReceivedCharacter = 0;
  currentMode = AWAITING_FRAME_HEADERS;
  Serial.print("Welcome!");
}

void loop()
{
  char c = Serial.read();
  if (c != NOTHING)
    receivedByte(c);
}




void receivedByte(unsigned char character) {
  if (currentMode == AWAITING_FRAME_HEADERS)
    match_headers(character);
  else 
    packetByeReceived(character);
}



void match_headers(unsigned char character) {
  if (lastReceivedCharacter == 0x59 && character == 0x59){
    currentMode = PARSE_MODE;
    lastReceivedCharacter = 0;  
  } else {
    lastReceivedCharacter = character;
  }
}

void packetByeReceived(unsigned char character) {
  distancePacket[currentPacketPosition++] = character;
  if (currentPacketPosition == DISTANCE_PACKET_LENGTH) {
    fullPacketReceived(distancePacket);
    currentPacketPosition = 0;
    currentMode = AWAITING_FRAME_HEADERS;
  }
}

float getStandardDeviation() {
  float mean = 0;
  for (int i = 0; i < DISTANCES_LENGTH; i++) {
    mean += distances[i];
  }
  mean /= DISTANCES_LENGTH;

  float squareDiffSum = 0;
  for (int i = 0; i < DISTANCES_LENGTH; i++) {
    squareDiffSum += pow(distances[i] - mean, 2);
  }
  return sqrt(squareDiffSum / DISTANCES_LENGTH);
}

void newDistanceSample(int distance) {
  distances[nextDistance++] = distance;
  nextDistance = nextDistance % DISTANCES_LENGTH;

  float standardDeviation = getStandardDeviation();
  
  if (standardDeviation > 1.0)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
    
//  mySerial.print("\r\nStd dev: ");
//  mySerial.print((int)standardDeviation, DEC);
//  mySerial.print(".");
//  int decimalPart = (standardDeviation - floor(standardDeviation)) * 100;
//  if (decimalPart < 10) mySerial.print(0, DEC);
//  mySerial.print(decimalPart, DEC);
}

void fullPacketReceived(unsigned char packet[]) {
  bool isChecksumValid(unsigned char packet[]);
  
  if (isChecksumValid(packet)) {
    int distance;
    distance = packet[0];
    distance += (packet[1] << 8);
//    mySerial.print("\r\nGot: ");
//    mySerial.print(distance, DEC);
   
    newDistanceSample(distance);
  }
}


bool isChecksumValid(unsigned char packet[]) {
  int sum = FRAME_HEADER + FRAME_HEADER;
  bool result;
  
  for (int i = 0; i < DISTANCE_PACKET_LENGTH - 1; i++) {
//    mySerial.print("\n\rdata ");
//    mySerial.print(i, DEC);
//    mySerial.print(" :");
//    mySerial.print(packet[i], DEC);
    sum += ((unsigned char)packet[i]);
//    mySerial.print("\n\rs:");
//    mySerial.print(sum, DEC);
  }
//  mySerial.print("\r\nCH: ");
//  mySerial.print(packet[6], DEC);

  sum = sum % 256;
  
  result = packet[CHECKSUM_INDEX] == sum;
  if (!result) {
      Serial.print("\n\rB");
//    mySerial.print("\n\rBad checksum. calculated: ");
//    mySerial.print(sum, DEC);
//    mySerial.print(" expected: ");
//    mySerial.print(packet[CHECKSUM_INDEX], DEC);
  }
  return result;
}
