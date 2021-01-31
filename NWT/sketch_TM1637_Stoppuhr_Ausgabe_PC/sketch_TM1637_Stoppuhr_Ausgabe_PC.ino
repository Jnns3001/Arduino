const int EingangTaster = 8;
int ZustandTaster;
unsigned long Zeit;
unsigned long Startzeit;
unsigned long Stoppzeit;

void setup(){

  Serial.begin(9600);
  pinMode(EingangTaster, INPUT_PULLUP);

}

void loop(){
  
  do{                                               //Erster Zustand Schalter - Start

    ZustandTaster = digitalRead(EingangTaster);
    
  } while (ZustandTaster==LOW  );
  
  Serial.println("start");
  Startzeit = millis();                             //Start Zeit speichern
  delay(300);

  do{                                               //Zweiter Zustand Schalter - Stopp
      ZustandTaster = digitalRead(EingangTaster);
      
  } while (ZustandTaster==LOW);

  
  Stoppzeit = millis();                             // Endzeit ausrechnen und ausgeben
  Zeit = Stoppzeit - Startzeit;

  Serial.println(Zeit);
  delay(1000);
}
