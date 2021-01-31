#include <TM1637Display.h>

const int sensorPin = A0;              // Analogen Eingang mit Variabler festlegen
int SensorWert = 0; 
TM1637Display siebensegment(2, 3);     //Siebensegmentanzeige festlegen

void setup() {
  siebensegment.setBrightness(5);
}

void loop() {
  SensorWert = analogRead(sensorPin);        
  Serial.println(SensorWert);
  siebensegment.showNumberDec(int(SensorWert*0.1 - 43));
  delay(500);
}
