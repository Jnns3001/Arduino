
// Pins:
#define WE 12  // Write Enable Active Low
#define OE 11  // Output Enable Active Low
#define CE 10  // Chip Enable Active Low
#define DQ0 9  // Data In/Out
#define DQ7 2

#define DS 17    // Serial Data Input
#define STCP 18  // Storage Register Clock Input
#define SHCP 19  // Shift Register Clock Input

bool OutMode = 1;

void setModeIn() {
  if (OutMode) {
    for (int pin = DQ7; pin <= DQ0; pin++) {
      pinMode(pin, INPUT);
    }
    OutMode = 0;
  }
  return;
}

void setModeOut() {
  if (!OutMode) {
    for (int pin = DQ7; pin <= DQ0; pin++) {
      pinMode(pin, OUTPUT);
    }
    OutMode = 1;
  }
  return;
}

void poll(byte trueData) {
  pinMode(DQ7, INPUT);
  Serial.println("polling");
  while(digitalRead(DQ7) != trueData & 0x80){}
  delay(100);
  Serial.println("done polling");
  pinMode(DQ7, OUTPUT);
  return;
}

void setAddress(int address) {
  shiftOut(DS, SHCP, MSBFIRST, (address >> 16));
  shiftOut(DS, SHCP, MSBFIRST, (address >> 8));
  shiftOut(DS, SHCP, MSBFIRST, address);

  digitalWrite(STCP, LOW);
  digitalWrite(STCP, HIGH);
  digitalWrite(STCP, LOW);
}

byte readByteFast(int address) {
  setAddress(address);
  byte data = 0;
  //delayMicroseconds(1); // Should not be necessary 70ns = 0,070us
  for (int pin = DQ7; pin <= DQ0; pin++) {
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

void writeByte(int address, byte data) {
  setAddress(address);
  // set Data Pins
  for (int pin = DQ0; pin >= DQ7; pin--) {
    digitalWrite(pin, data & 1);
    data = data >> 1;
  }

  digitalWrite(WE, 0);
  delayMicroseconds(1);
  digitalWrite(WE, 1);

  return;
}

void writeByteSafe(int address, byte data) {
  digitalWrite(OE, 1); // just to be safe
  setModeOut();

  writeByte(0x5555, 0xAA);
  writeByte(0x2AAA, 0x55);
  writeByte(0x5555, 0xA0);
  writeByte(address, data);
  poll(data);

  return;
}

void sectorErase(int address) {
  digitalWrite(OE, 1); // just to be safe
  setModeOut();

  writeByte(0x5555, 0xAA);
  writeByte(0x2AAA, 0x55);
  writeByte(0x5555, 0x80);
  writeByte(0x5555, 0xAA);
  writeByte(0x2AAA, 0x55);
  writeByte(address, 0x30);
  poll(0xFF);

  return;
}

void chipErase() {
  Serial.println("Erasing Chip");
  digitalWrite(OE, 1); // just to be safe
  setModeOut();

  writeByte(0x5555, 0xAA);
  writeByte(0x2AAA, 0x55);
  writeByte(0x5555, 0x80);
  writeByte(0x5555, 0xAA);
  writeByte(0x2AAA, 0x55);
  writeByte(0x5555, 0x10);
  poll(0xFF);
  Serial.println("Done Erasing Chip");
  return;
}

byte readByteSafe(int address) {
  setModeIn();
  digitalWrite(OE, 0);
  byte data = readByteFast(address);
  digitalWrite(OE, 1);
  return data;
}

byte* readSector(int startAddress, int stopAddress) {
  setModeIn();
  digitalWrite(OE, 0);

  int sectorLen = stopAddress - startAddress;
  byte data[sectorLen];
  for (int address = startAddress; address <= stopAddress; address++) {
    data[address - startAddress] = readByteFast(address);
  }

  digitalWrite(OE, 1);
  return data;
}

void dumpSectorToSerial(int startAddress, int stopAddress) {
  Serial.println("Print Sector");
  startAddress = startAddress - startAddress % 16;
  stopAddress = stopAddress - stopAddress % 16 + 16;
  for (int base = startAddress; base < stopAddress; base += 16) {
    byte *data = readSector(base, base + 16);
    char buf[80];
    sprintf(buf, "0%03x: %02x %02x %02x %02x %02x %02x %02x %02x    %02x %02x %02x %02x %02x %02x %02x %02x",
            base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
            data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
    Serial.println(buf);
  }
}


void setup() {
    // all inactive, chip on
  digitalWrite(WE, 1);
  digitalWrite(OE, 1);
  digitalWrite(CE, 0);
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(CE, OUTPUT);

  setModeIn();

  pinMode(DS, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);

  Serial.begin(57600);
  Serial.println("Serial StartUp");

  chipErase();
  dumpSectorToSerial(1, 0xFF);
}

void loop() {
  // put your main code here, to run repeatedly:
}
