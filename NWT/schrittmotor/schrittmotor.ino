void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
}
  int org = 7;
  int brn = 3;
  int yel = 4;
  int red = 5;
  int richtung;
  int ZustandTaster;
  int pause = 100;
  
void loop() {
  
  ZustandTaster = digitalRead(6);
  if(ZustandTaster == 1){
    
    richtung++;
    richtung = richtung % 2;
  }
  
  Serial.print(richtung);
  

  if(richtung == 1){
  
    digitalWrite(brn, HIGH);            //step 1
    digitalWrite(red, HIGH);
    digitalWrite(org, LOW);
    digitalWrite(yel, LOW);
    delay(pause);
    
    digitalWrite(brn, LOW);            //step 2
    digitalWrite(red, HIGH);
    digitalWrite(org, HIGH);
    digitalWrite(yel, LOW);
    delay(pause);
    
    digitalWrite(brn, LOW);            //step 3
    digitalWrite(red, LOW);
    digitalWrite(org, HIGH);
    digitalWrite(yel, HIGH);
    delay(pause);
  
    digitalWrite(brn, HIGH);            //step 4
    digitalWrite(red, LOW);
    digitalWrite(org, LOW);
    digitalWrite(yel, HIGH);
    delay(pause);
  }
  
  if(richtung == 0){
    digitalWrite(brn, HIGH);            //step 4
    digitalWrite(red, LOW);
    digitalWrite(org, LOW);
    digitalWrite(yel, HIGH);
    delay(pause);
    
    digitalWrite(brn, LOW);            //step 3
    digitalWrite(red, LOW);
    digitalWrite(org, HIGH);
    digitalWrite(yel, HIGH);
    delay(pause);
  
    digitalWrite(brn, LOW);            //step 2
    digitalWrite(red, HIGH);
    digitalWrite(org, HIGH);
    digitalWrite(yel, LOW);
    delay(pause);
    
    digitalWrite(brn, HIGH);            //step 1
    digitalWrite(red, HIGH);
    digitalWrite(org, LOW);
    digitalWrite(yel, LOW);
    delay(pause);
  }
}
