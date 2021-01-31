#include <TM1637Display.h>

const int sensorPin = A0;                             // Analogen Eingang mit Variabler festlegen
int SensorWert = 0;
int Ausgabe = 0;
TM1637Display siebensegment(2, 3);                    //Siebensegmentanzeige festlegen

void setup() {
  siebensegment.setBrightness(5);                     //Pins und Siebensegmentanzeige einrichten
  pinMode(7, OUTPUT);
}

void loop() {
  int ledPin = 9;
  SensorWert = analogRead(sensorPin);                 // SensorWert auslesen
  Serial.println(SensorWert);
  siebensegment.showNumberDec(int(SensorWert));       //zur Kontrolle ausgeben

  Ausgabe = SensorWert / 4;                           //Wert anpassen

  if (Ausgabe > 255){                                 //Overflow ausschliesen
    Ausgabe = 255;
  }

  analogWrite(ledPin, Ausgabe);                       //Ausgabe des Wertes bzw. an die LED
  Serial.println(Ausgabe);

  delay(500);
}
