const int EingangTaster = 8;

int ZustandTaster;



void setup() {

  Serial.begin(9600);

  pinMode(EingangTaster, INPUT_PULLUP);

}



void loop() {

  ZustandTaster = digitalRead(EingangTaster);

  Serial.print("Zustand: ");

  Serial.print(ZustandTaster);

  Serial.print("\n");

  delay(10);                  

}
