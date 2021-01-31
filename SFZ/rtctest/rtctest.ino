#include <Time.h> Bibliotheken laden
#include <Wire.h>
#include <DS1307RTC.h>

void setup() {
  setTime(16,22,0,26,2,2020);
  Serial.begin(9600); //Öffnet den seriellen Port und legt die Baud Rate (9600) für die serielle Übertragung fest.
  setSyncProvider(RTC.get); //Dies ist die Funktion um die Zeit- und Datumsangabe von der RTC zu bekommen
}

void loop(){
  Serial.print(hour()); //Serial.print ist der Befehl etwas im seriellen Monitor anzuzeigen (Stunde, Minute, Sekunde, Leerzeichen, Tag, Leerzeichen, usw.)
  printDigits(minute()); //bei den Minuten und Sekunden wird der Befehl
  printDigits(second()); //printDigits angegeben welcher am Ende des Codes noch festgelegt wird.
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
  delay(1000); //warte eine Sekunde


  //Serial.print(__TIME__);
 
}

void printDigits(int digits){ //In diesem Abschnitt wird festgelgt, dass bei Zahlen <10 im seriellen Monitor automatisch eine 0 vor den Ziffern angezeigt wird. Das gilt nur für den seriellen Monitor und nicht für LCD Display.
  Serial.print(":"); 
  if(digits < 10) 
  Serial.print('0'); 
  Serial.print(digits); 
}
