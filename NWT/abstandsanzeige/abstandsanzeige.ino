#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigger=2;                                // Arduino Pin fuer HC-SR04 Trig
const int echo=3;                                   // Arduino Pin fuer HC-SR04 Echo
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup(){
  Serial.begin(9600);                                         //display
  lcd.init();
  Wire.begin();

  pinMode(trigger, OUTPUT);                                   // Abstandsmessung
  pinMode(echo, INPUT);
  digitalWrite(trigger, HIGH); //Signal abschalten
  Serial.print("Abstandsmessung:\n\n");
}


void loop(){
  int strecke = getStrecke();         //Abstandsmessung
  if(strecke < 0){
    strecke = 0;
  }
  Serial.print(strecke);
  Serial.println("mm");
  

  lcd.clear();                                      //Ausgabe am Display
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print(strecke);
  lcd.setCursor(8,0);
  lcd.print("mm");
  noTone(9);

  if(strecke < 100){
    Serial.print("Stopp");
    lcd.setCursor(3,1);
    lcd.print("Stopp");
    tone(9, 1000);
  }
  else if(strecke < 200){
    Serial.print("Achtung");
    lcd.setCursor(3,1);
    lcd.print("Achtung");
    tone(9, 500);
  }
  else if(strecke < 500){
    Serial.print("Hinderniss");
    lcd.setCursor(3,1);
    lcd.print("Hinderniss");
    tone(9, 200);
  }
  delay(500);
}

int getSignalZeit(){
  int zeit=0;
  //Ausschalten und ganz kurz warten, dass der Sender sicher aus ist
  digitalWrite(trigger, LOW);
  delayMicroseconds(3);
  //Einen Impuls von 10 Microsekunden senden
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  //wieder Ausschalten
  digitalWrite(trigger, LOW);
  //Die Zeit messen, die vergeht bis das Signal zurück ist
  zeit = int(pulseIn(echo, HIGH));
  //Die Funktion soll genau diese Zeit zurückgeben
  return(zeit);
}

int getStrecke(){
  int zeits = getSignalZeit();
  int way = 0;

  way = int((0.334 * zeits)/2);
  return(way);
  return(zeits);
}

