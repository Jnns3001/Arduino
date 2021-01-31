int ledPin = 9;         // LED am digital Pin 9

const int pause = 60;   //Pause in der Schleife



void setup() {

  // Setup nicht notwendig

}



void loop() {



  //LED langsam einschalten

  for (int helligkeit = 1 ; helligkeit < 255; helligkeit=helligkeit*2) {

    // sets the value (range from 0 to 255):

    analogWrite(ledPin, helligkeit);

    delay(pause);

  }



  //LED langsam ausschalten

  for (int helligkeit = 255 ; helligkeit > 0; helligkeit=helligkeit/2) {

    analogWrite(ledPin, helligkeit);

    delay(pause);

  }



}
