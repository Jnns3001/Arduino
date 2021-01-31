#include <TM1637Display.h>
// Analogen Eingang mit Variabler festlegen
const int sensorPin = A0;   
int SensorWert = 0; //Siebensegmentanzeige festlegen
TM1637Display siebensegment(2, 3);

void setup() {
  siebensegment.setBrightness(5);
}

void loop() {
  SensorWert = analogRead(sensorPin);
  siebensegment.showNumberDec(SensorWert);
  delay(500);
}
