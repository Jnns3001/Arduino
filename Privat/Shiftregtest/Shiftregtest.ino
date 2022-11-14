#define SHIFT_DATA 2
#define SHIFT_CLK 4
#define SHIFT_LATCH 3


void setAddress(int address) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, address);
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 16));

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);


  setAddress(0xFEDCBA);
}

void loop() {
  // put your main code here, to run repeatedly:

}
