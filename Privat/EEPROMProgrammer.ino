/**
 * Code for Programmer
 * 
*/

#define SHIFT_DATA 1
#define SHIFT_CLK 2
#define SHIFT_LATCH 3
#define SHIFT_RST 4

#define DATA0 8
#define DATA7 15

#define WRITE_EN 5 // active low
#define OUTPUT_EN 6 // active low
#define CHIP_EN 7 // active low


void setAddress(int address) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, address);
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 16));

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}


byte readMEM(int address){
  pinMode(OUTPUT_EN, LOW); //active low 
  for (int pin = DATA0; pin <= DATA7; pin +=1){
    pinMode(pin, INPUT);
  }
  setAddress(address);

  byte data = 0;
  for (int pin = DATA7; pin >= DATA0; pin-=1){
    data = (data << 1) + digitalRead(pin)
  }
  return data
}


void writeMEM(int address, byte data){
  pinMode(OUTPUT_EN, HIGH); //active low
  for (int pin = DATA0; pin <= DATA7; pin +=1){
    pinMode(pin, OUTPUT);
  }

}





void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:

}
