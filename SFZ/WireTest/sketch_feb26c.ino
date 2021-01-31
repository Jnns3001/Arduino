
#include <Wire.h>
 
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  Wire.begin();
  while(1)
  {
    Wire.beginTransmission(0x68);
    byte error = Wire.endTransmission();
    if (error)
    {
      Serial.println(F("RTC ERROR"));
      delay(250);
    }
    else break;
  }
  Serial.println(F("RTC ready"));
}

void loop() {}
