#include <TM1637Display.h>

const int sensorPin = A0;              // Analogen Eingang mit Variabler festlegen
int SensorWert = 0; 
TM1637Display siebensegment(2, 3);     //Siebensegmentanzeige festlegen

void setup() {
  siebensegment.setBrightness(5);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  int gruene_LED = 5;                             /*Deklaration der LEDs*/
  int gelbe_LED = 6;
  int rote_LED = 7;
  SensorWert = analogRead(sensorPin);        
  Serial.println(SensorWert);
  siebensegment.showNumberDec(int(SensorWert));
  delay(500);

  if (SensorWert < 200){
    digitalWrite(gelbe_LED, LOW);                   
    digitalWrite(rote_LED, LOW); 
    digitalWrite(gruene_LED, HIGH);
  }
  else if (500 > SensorWert){
    digitalWrite(gelbe_LED, HIGH);                   
    digitalWrite(rote_LED, LOW); 
    digitalWrite(gruene_LED, LOW);
  }
  else{
    digitalWrite(gelbe_LED, LOW);                   
    digitalWrite(rote_LED, HIGH); 
    digitalWrite(gruene_LED, LOW);
  }
}
