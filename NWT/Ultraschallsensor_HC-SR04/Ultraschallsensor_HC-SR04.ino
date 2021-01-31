//Anschluesse definieren
const int trigger=2; // Arduino Pin fuer HC-SR04 Trig
const int echo=3;    // Arduino Pin fuer HC-SR04 Echo

//Anschlüsse und serielles Terminal Initialisieren
void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, HIGH); //Signal abschalten

  // Serielles Terminal:
  Serial.begin(9600);
  Serial.println("Abstandsmessung:\n\n");
}

//Messschleife
void loop() {

  int strecke = getStrecke();
  Serial.print(strecke);
  Serial.println("mm");
  delay(500);
}

// Entfernung in cm über gewöhnlichen Ultraschallsensor mit Echo und Trigger messen
// Eine eigene Funktion, die die Zeit misst
int getSignalZeit(){
  int zeit=0;
  //Ausschalten und ganz kurz warten, dass der Sender sicher aus ist
  digitalWrite(trigger, LOW);
  delayMicroseconds(3);
  //Einen Impuls von 10 Microsekunden senden
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  //wieder Ausschalten
  digitalWrite(trigger, LOW);
  //Die Zeit messen, die vergeht bis das Signal zurück ist
  zeit = int(pulseIn(echo, HIGH));
  //Die Funktion soll genau diese Zeit zurückgeben
  return(zeit);
}

int getStrecke(){
  int zeits = getSignalZeit();
  int way = 0;

  way = int((0.334 * zeits)/2);
  return(way);
  return(zeits);
}
