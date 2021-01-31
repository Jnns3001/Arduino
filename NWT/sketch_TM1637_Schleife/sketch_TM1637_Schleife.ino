const int EingangTaster = 8;

int ZustandTaster;



void setup() {

  Serial.begin(9600);

  pinMode(EingangTaster, INPUT_PULLUP);

}



void loop() {

do{

  ZustandTaster = digitalRead(EingangTaster);

} while (ZustandTaster==HIGH);

  Serial.print("Hallo\n");

  delay(500);                  

}
