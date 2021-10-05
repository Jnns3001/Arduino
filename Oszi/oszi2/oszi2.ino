#define voltage A0 

void setup() { 
   Serial.begin(115200); 
   pinMode(voltage, INPUT); 
} 
void loop() { 
   int resistorValue = analogRead(voltage); 
   double v = map(resistorValue,0,1023,0,50); 
   Serial.println(v/10, 2); 
   //Serial.println("V");
   delay(100); 
}