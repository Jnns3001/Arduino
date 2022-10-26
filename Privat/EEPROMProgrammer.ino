/**
 * Code for Programmer
 * 
*/

#define SHIFT_DATA 1
#define SHIFT_CLK 2
#define SHIFT_LATCH 3
#define SHIFT_RST 4

#define WRITE_EN 5 // active low
#define OUTPUT_EN 6 // active low
#define CHIP_EN 7 // active low

void setAddress(int address, bool outputEnable) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, address);
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 16));

  if(outputEnable){
    digitalWrite(SHIFT_LATCH, LOW);
    digitalWrite(SHIFT_LATCH, HIGH);
    digitalWrite(SHIFT_LATCH, LOW);
  }
}

void setData(byte data, bool outputEnable) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, data);

  if(outputEnable){
    digitalWrite(SHIFT_LATCH, LOW);
    digitalWrite(SHIFT_LATCH, HIGH);
    digitalWrite(SHIFT_LATCH, LOW);
  }
}


void writeEEPROM(int address,





void setup() {

  pinMode(, OUTPUT);
  pinMode(, OUTPUT);
  pinMode(, OUTPUT);
  pinMode(, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
