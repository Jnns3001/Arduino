#define SHIFT_DATA 2
#define SHIFT_CLK 4
#define SHIFT_LATCH 3
//#define SHIFT_RST 5 // active low

#define DATA0 19
#define DATA7 12

#define WE 6 // active low
#define OE 7 // active low


void init(){
  digitalWrite(WE, HIGH);
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);

  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);

  Serial.begin(9600);
  delay(2000);
  Serial.println("intialising Serial COM");
}

void setIO(bool Input){
  if(Input){
    for (int pin = DATA0; pin >= DATA7; pin -=1){
      pinMode(pin, INPUT);
    }
  }
  else{
    for (int pin = DATA0; pin >= DATA7; pin -=1){
      pinMode(pin, OUTPUT);
    }
  }
}

void setAddress(int address) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, address);
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 16));

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}

void setByte(byte out){
  setIO(0);
  for(int i=0; i<8; i++){
    digitalWrite(DATA0 - i, bitRead(out, i));
  }
}

byte readByte(int address){
  setIO(1);

  digitalWrite(WE, HIGH);
  
  setAddress(address);
  
  digitalWrite(OE, LOW);
  delayMicroseconds(5);

  byte data = 0;

  for (int pin = DATA7; pin <= DATA0; pin +=1){
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

void writeByte(byte data, int address){
  setIO(0);
  digitalWrite(OE, HIGH);
  digitalWrite(WE, HIGH);

  setAddress(address);
  setByte(data);

  digitalWrite(WE, LOW);
  delayMicroseconds(1);
  digitalWrite(WE, HIGH); 

}

void printContents(int len) {
  setIO(1);

  for (int base = 0; base <= len; base += 32) {
    byte data[32];
    for (int offset = 0; offset <= 31; offset += 1) {
      data[offset] = readByte(base + offset);
    }
    char buf[500];
    sprintf(
      buf,
      "%03x: %02x %02x %02x %02x %02x %02x %02x %02x  %02x %02x %02x %02x %02x %02x %02x %02x  |  %02x %02x %02x %02x %02x %02x %02x %02x  %02x %02x %02x %02x %02x %02x %02x %02x",
      base, 
      data[0],  data[1],  data[2],  data[3],  data[4],  data[5],  data[6],  data[7],  data[8],  data[9],  data[10], data[11], data[12], data[13], data[14], data[15],
      data[16], data[17], data[18], data[19], data[20], data[21], data[22], data[23], data[24], data[25], data[26], data[27], data[28], data[29], data[30], data[31]);

    Serial.println(buf);
  }
}

void programByte(byte data, int address){
  setIO(0);

  writeByte(data, address);
  
  delayMicroseconds(30);
}

void eraseChip(){
  setIO(0);

  for(int addr = 0; addr <= 8192; addr ++){
    programData(0xFF,addr);
  }
}

void programData(byte[] data, int[] address){
  


}

void setup(){
  init();

  eraseChip();
  programByte(0x45, 0x000F);

  printContents(0x10);
}

void loop() {
}