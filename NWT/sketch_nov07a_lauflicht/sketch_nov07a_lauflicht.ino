
void setup () {

Serial.begin(9600);

}

void loop (){

  pinMode( 5, OUTPUT);  // deklaration pins
  pinMode( 6, OUTPUT);
  pinMode( 7, OUTPUT);
  pinMode( 8, OUTPUT);
  
  pinMode( 9, OUTPUT);
  pinMode( 10, OUTPUT);
  pinMode( 11, OUTPUT);
  pinMode( 12, OUTPUT);


  for (int i=5; i <= 12; i=i+1){

    Serial.print(" ");   // Ausgabe von i
    Serial.print(i);

    digitalWrite(i, HIGH);  // Port i high

    delay(200);

    digitalWrite(i, LOW);   // Port i low

  };

}
