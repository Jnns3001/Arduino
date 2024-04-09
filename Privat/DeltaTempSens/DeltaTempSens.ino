#include <DS18B20.h>
#include "InterpolationLib.h"

DS18B20 ds(2);

float temps[2];
float deltaT;
uint8_t addresses[2][8];
float dT[10];

void shiftDT(float dt[10], float newDT) {
  for(int i = 0; i < 9; i++) {
    dt[i] = dt[i+1];
  }
  dt[9] = newDT;
}

void setup() {
  Serial.begin(9600);
  int activeDevice;

  while(ds.selectNext()) {
    ds.getAddress(addresses[activeDevice]);
    for(uint8_t i = 0; i < 8; i++){
      Serial.print(addresses[activeDevice][i], HEX);
    }
    Serial.println("");
    activeDevice++;
  }
}

void loop() {
  for(int a = 0; a < 2; a++) {
    ds.select(addresses[a]);
    temps[a] = ds.getTempC();
  }

  deltaT = temps[0] - temps[1];

  shiftDT(dT, deltaT);

  Serial.print(temps[0], 4);
  Serial.print(", ");
  Serial.print(deltaT, 4);
  Serial.print(", ");
  Serial.println(dT[9], 4);
}
