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
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
