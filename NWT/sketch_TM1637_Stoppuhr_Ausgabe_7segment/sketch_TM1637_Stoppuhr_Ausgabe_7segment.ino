const int EingangTaster = 8;
int ZustandTaster;
unsigned long startzeit;
unsigned long stoppzeit;
unsigned long zeitausgabe;
unsigned long zeit;

#include <TM1637Display.h>
TM1637Display anzeige(2, 3);

void setup(){
  
  anzeige.setBrightness(5);
  Serial.begin(9600);
  pinMode(EingangTaster, INPUT_PULLUP);

}

void loop(){
  
  do{                                               //Erster Zustand Schalter - Start

    ZustandTaster = digitalRead(EingangTaster);
    
  } while (ZustandTaster==LOW  );
  
  anzeige.clear();
  Serial.println("start");
  startzeit = millis();                             //Start Zeit speichern
  delay(300);

  do{                                               //Zweiter Zustand Schalter - Stopp
      ZustandTaster = digitalRead(EingangTaster);
      
  } while (ZustandTaster==LOW);

  
  stoppzeit = millis();                             // Endzeit ausrechnen und ausgeben
  zeitausgabe = stoppzeit - startzeit;
  zeit = zeitausgabe / 10;

  anzeige.showNumberDecEx(zeit,64);
  Serial.println(zeitausgabe);
  
  delay(1000);
}
