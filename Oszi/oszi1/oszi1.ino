int sensorPin = A0;
void setup(){
    Serial.begin(115200);
}
void loop(){
    int val = analogRead(sensorPin);
    Serial.println(val);
}