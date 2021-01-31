
// Tiny RTC (DS1307)

#include <Wire.h>    // I2C-Bibliothek einbinden
#include "RTClib.h"  // RTC-Bibliothek einbinden

DS1307 RTC;      // RTC Modul

void setup(void) {

  // Initialisiere I2C 
  Wire.begin();
 
  // Initialisiere RTC
  RTC.begin();

  // Serielle Ausgabe starten
  Serial.begin(9600);

  // Begruesungstext auf seriellem Monitor ausgeben
  Serial.println("Starte Datum und Zeit - blog.simtronyx.de");

  // Pruefen ob RTC laeuft 
  if (! RTC.isrunning()) {
   
    // Aktuelles Datum und Zeit setzen, falls die Uhr noch nicht laeuft
    RTC.adjust(DateTime(__DATE__, __TIME__));

    Serial.println("datum: " __DATE__);
    
    Serial.println("Echtzeituhr wurde gestartet und auf Systemzeit gesetzt.");
  }
  else Serial.println("Echtzeituhr laeuft bereits.");

}

void loop(){
 
  DateTime now=RTC.now(); // aktuelle Zeit abrufen
  
  Serial.println(DateTime);
 
  show_time_and_date(now);  // Datum und Uhrzeit ausgeben
 
  delay(30000); // 30 Sekunden warten bis zur naechsten Ausgabe
}

// Wochentag ermitteln
String get_day_of_week(uint8_t dow){
 
  String dows="  ";
  switch(dow){
   case 0: dows="So"; break;
   case 1: dows="Mo"; break;
   case 2: dows="Di"; break;
   case 3: dows="Mi"; break;
   case 4: dows="Do"; break;
   case 5: dows="Fr"; break;
   case 6: dows="Sa"; break;
  }
 
  return dows;
}

// Datum und Uhrzeit ausgeben
void show_time_and_date(DateTime datetime){
 
  // Wochentag, Tag.Monat.Jahr
  Serial.print(get_day_of_week(datetime.dayOfWeek()));
  Serial.print(", ");
  if(datetime.day()<10)Serial.print(0);
  Serial.print(datetime.day(),DEC);
  Serial.print(".");
  if(datetime.month()<10)Serial.print(0);
  Serial.print(datetime.month(),DEC);
  Serial.print(".");
  Serial.println(datetime.year(),DEC);
 
  // Stunde:Minute:Sekunde
  if(datetime.hour()<10)Serial.print(0);
  Serial.print(datetime.hour(),DEC);
  Serial.print(":");
  if(datetime.minute()<10)Serial.print(0);
  Serial.print(datetime.minute(),DEC);
  Serial.print(":");
  if(datetime.second()<10)Serial.print(0);
  Serial.println(datetime.second(),DEC);
}
