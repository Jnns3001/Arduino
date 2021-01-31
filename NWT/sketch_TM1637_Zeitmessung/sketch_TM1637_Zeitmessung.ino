unsigned long Zeit;

void setup(){

  Serial.begin(9600);

}

void loop(){

  Serial.print("vergangene Zeit: ");

  Zeit = millis();



  Serial.println(Zeit);  

  delay(1000);

}
