#include <TM1637Display.h>

TM1637Display anzeige(2, 3);



void setup() {

     

}



void loop() {

  for (int i=0; i <= 100; i=i+1){

  anzeige.setBrightness(i);
  
  anzeige.clear();

  delay(100);

  anzeige.showNumberDec(i);

  delay(1000);
  }

}
