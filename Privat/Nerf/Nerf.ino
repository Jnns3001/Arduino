#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

const int trigger = 2;
const int fireChange = 3;
const int flyWheel = 4;
const int voltage = 5;

const int motorFw = 6;
const int motorSh = 7;
const int led = 8;

int randNumber = 1000 * random(3);
int force;

void setPinModes(){
  pinMode(trigger, INPUT);
  pinMode(fireChange, INPUT);
  pinMode(flyWheel, INPUT);
  pinMode(voltage, INPUT);

  pinMode(motorFw, OUTPUT);
  pinMode(motorSh, OUTPUT); 
  pinMode(led, OUTPUT);
}

void doblink(int blinktime){
  digitalWrite(led, HIGH);
  delay(blinktime);
  digitalWrite(led, LOW);
}

void alloff(){
  digitalWrite(led, LOW);
  digitalWrite(motorFw, LOW);
  digitalWrite(motorSh, LOW);
}

void sleep(){
  for (int i=0; i <= 3; i=i+1){
    doblink(1000);
    Serial.println("sleep");
    alloff();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    while(true){
      Serial.println("can´t sleep");
      delay(10000);
    }
  }
}

void voltageCheck(){
  if(analogRead(voltage) <= 800){
    Serial.println("battery low");
    sleep();
  }
  else{
    Serial.println("battery OK");
  }
}

void shoot(){
  digitalWrite(motorSh, HIGH);
  delay(20);
  digitalWrite(motorSh, LOW);
}

void kidsafe(){
  Serial.println("check authorization");
  doblink(randNumber*100);
  delay(500);

  if(digitalRead(trigger) == false){
    Serial.println("not authorized 1");
    sleep();
  }
  else{
    doblink(10);
    int starttime = micros();
    while(digitalRead(trigger) == true){
      delay(1);
    }
    int stoptime = micros();

    int wholetime = stoptime - starttime;

    if(wholetime < (randNumber + 500)){
      if(wholetime > (randNumber - 500)){
        Serial.println("authorized");
      }
      else{
        Serial.println("not authorized 2");
        sleep();
      }
    }
    else{
      Serial.println("not authorized 3");
      sleep();
    }
  }
}

void getforce(){
  doblink(100);
  doblink(200);
  doblink(300);
  delay(500);
  doblink(10);
  
  int starttime = micros();
  while(digitalRead(trigger) == true){
    delay(1);
  }
  int stoptime = micros();
  int wholetime = stoptime - starttime;
  
  if(wholetime >= 2550){
    force = 255;
  }
  else{
    force = wholetime/10;
  }
  
  Serial.println(force);
}

void setup() {
  Serial.begin(9600);
  setPinModes();

  doblink(10);

  voltageCheck();
  kidsafe();
  getforce();
}

void loop(){
  Serial.println("starting shoot loop");
  voltageCheck();
  
  if(digitalRead(flyWheel) == true){
    digitalWrite(motorFw, HIGH);
    while(digitalRead(trigger) == true){
      if(digitalRead(fireChange) == false){               //Full Auto == True
        analogWrite(motorFw, force);
        shoot();
        while(digitalRead(trigger) == true){
          delay(1);
        }
      }
      else{
        shoot();
      }
    }
  }
  else{
    digitalWrite(motorFw, LOW);
  }
}
