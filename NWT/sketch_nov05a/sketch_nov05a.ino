void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  int gruene_LED = 5;
  int gelbe_LED = 6;
  int rote_LED = 7;
  
  digitalWrite(gelbe_LED, LOW);
  digitalWrite(rote_LED, LOW); 
  digitalWrite(gruene_LED, HIGH);
  delay(3000);
  
  digitalWrite(gruene_LED, LOW);
  digitalWrite(gelbe_LED, HIGH);
  delay(1000);
  
  digitalWrite(gelbe_LED, LOW);
  digitalWrite(rote_LED, HIGH);
  delay(3000);
  
  digitalWrite(gelbe_LED, HIGH);
  delay(1000); 
}
