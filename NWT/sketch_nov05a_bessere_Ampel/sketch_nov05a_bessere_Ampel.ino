void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  int gruene_LED = 5;                             /*Deklaration der LEDs*/
  int gelbe_LED = 6;
  int rote_LED = 7;
  
  digitalWrite(gelbe_LED, LOW);                   /*Gelb und Rot gehen aus und Grün geht an*/
  digitalWrite(rote_LED, LOW); 
  digitalWrite(gruene_LED, HIGH);
  delay(3000);
  
  digitalWrite(gruene_LED, LOW);                  /* Grün geht aus und Gelb geht an*/
  digitalWrite(gelbe_LED, HIGH);
  delay(1000);
  
  digitalWrite(gelbe_LED, LOW);                   /*gelb geht aus und rot geht an */
  digitalWrite(rote_LED, HIGH);
  delay(3000);
  
  digitalWrite(gelbe_LED, HIGH);                  /*gelb geht zusätzlich an*/
  delay(1000); 
}
