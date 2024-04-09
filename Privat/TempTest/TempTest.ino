#include <DS18B20.h>

DS18B20 ds(2);

float temp1;
float temp2;
bool activeDevice;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while(ds.selectNext()) {
    float t = ds.getTempC();

    activeDevice ? temp1 = t : temp2 = t;
    //activeDevice++;

    //Serial.print("deltaT: ");
    Serial.println(temp1 - temp2); 
  }
}
