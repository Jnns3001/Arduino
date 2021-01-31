#include <Time.h> Bibliotheken laden
#include <Wire.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //In dieser Zeile wird festgelegt, welche Pins des Mikrocontrollerboards für das LCD verwendet wird

void setup() {
    lcd.begin(16, 2); //Im Setup wird angegeben, wie viele Zeichen und Zeilen werwendet werden.
    Serial.begin(9600); //Öffnet den seriellen Port und legt die Baud Rate (9600) für die serielle Übertragung fest.
    setSyncProvider(RTC.get); //Dies ist die Funktion um die Zeit- und Datumsangabe von der RTC zu bekommen
}

void loop() {
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
    lcd.setCursor(2, 0); //setCursor gibt an wo der Text beginnen soll. In diesem Fall beim dritten Zeichen in der ersten Reihe.
    lcd.print(hour()); //Hier soll jetzt die Uhrzeit angezeigt werden, also „hour“ „:“ „minute“ usw..
    lcd.print(":");
    lcd.print (minute());
    lcd.print(":");
    lcd.print(second());
    lcd.print(" ");
    lcd.print("Uhr"); //Hier soll nach der Uhrzeit noch das Wort „Uhr“ angezeigt werden, dazu müssen noch3 Leerzeichen folgen, sonst würde bei Zahlen <10 immer ein weiteres „r“ hinter Uhr angezeigt werden. Das liegt daran, dass in der LCD Library der Befehl eine 0 vor Zahlen <10 anzuzeigen nicht vorhanden ist.
    lcd.print(" ");
    lcd.print(" ");
    lcd.print(" "); 
    lcd.setCursor(1, 1); // Der nächste „Text“ soll nun beim zweiten Zeichen in der zweiten Reihe beginnen.
    lcd.print(day()); // Das Datum soll nun als
    lcd.print("."); // „Tag“, „.“ „Monat“ usw. angegeben werden.
    lcd.print(month());
    lcd.print(".");
    lcd.print(year());
}

void printDigits(int digits){ //In diesem Abschnitt wird festgelgt, dass bei Zahlen <10 im seriellen Monitor automatisch eine 0 vor den Ziffern angezeigt wird. Das gilt nur für den seriellen Monitor und nicht für LCD Display.
    Serial.print(":"); 
    if(digits < 10) 
    Serial.print('0'); 
    Serial.print(digits); 
}







// Tiny RTC (DS1307)

#include <Wire.h>    // I2C-Bibliothek einbinden
#include "RTClib.h"  // RTC-Bibliothek einbinden

RTC_DS1307 RTC;      // RTC Modul

void setup(void) {

  // Initialisiere I2C 
  Wire.begin();
 
  // Initialisiere RTC
  RTC.begin();

  // Serielle Ausgabe starten
  Serial.begin(9600);

  // BegrÃ¼ÃŸungstext auf seriellem Monitor ausgeben
  Serial.println("Starte Datum und Zeit - blog.simtronyx.de");

  // Pruefen ob RTC laeuft 
  if (! RTC.isrunning()) {
   
    // Aktuelles Datum und Zeit setzen, falls die Uhr noch nicht laeuft
    RTC.adjust(DateTime(__DATE__, __TIME__));
   
    Serial.println("Echtzeituhr wurde gestartet und auf Systemzeit gesetzt.");
  }
  else Serial.println("Echtzeituhr laeuft bereits.");

}

void loop(){
 
  DateTime now=RTC.now(); // aktuelle Zeit abrufen
 
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
