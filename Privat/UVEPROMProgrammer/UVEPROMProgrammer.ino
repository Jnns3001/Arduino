#define SHIFT_DATA 18
#define SHIFT_CLK 16
#define SHIFT_LATCH 17

#define Vpp12v 19 // active low
#define Vpp6v 20 // active low

#define DATA0 0
#define DATA7 7

#define CE 8 // active low
#define OE 9 // active low

//size of Memory
#define MAXADDRESS 32768


void doinit(){
  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);
  digitalWrite(Vpp6v, HIGH);
  digitalWrite(Vpp12v, HIGH);
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(Vpp6v, OUTPUT);
  pinMode(Vpp12v, OUTPUT);


  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);

  Serial.begin(9600);
  while(!Serial){delay(100);}
  Serial.println("intialising Serial COM");

  setVpp(0);
}

void setIO(bool Input){
  if(Input){
    for (int pin = DATA0; pin <= DATA7; pin ++){
      pinMode(pin, INPUT);
    }
  }
  else{
    for (int pin = DATA0; pin <= DATA7; pin ++){
      pinMode(pin, OUTPUT);
    }
  }
}

void setVpp(bool Input){
  if(Input){
    digitalWrite(Vpp6v, HIGH);
    delay(1000);
    digitalWrite(Vpp12v, LOW);
    delay(3000);
    Serial.println("12V enabled");
  }
  else{
    digitalWrite(Vpp12v, HIGH);
    delay(1000);
    digitalWrite(Vpp6v, LOW);
    delay(3000);
    Serial.println("12V disabled");
  }
}

void setAddress(int address){
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, address);
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 16));

  digitalWrite(SHIFT_LATCH, LOW);
  delayMicroseconds(1);
  digitalWrite(SHIFT_LATCH, HIGH);
  delayMicroseconds(1);
  digitalWrite(SHIFT_LATCH, LOW);
}

void setByte(byte out){
  setIO(0);
  for(int i=0; i<8; i++){
    digitalWrite(DATA0 + i, bitRead(out, i));
  }
}

byte readByte(int address){
  setIO(1);

  digitalWrite(CE, LOW);
  
  setAddress(address);
  
  digitalWrite(OE, LOW);
  delayMicroseconds(1); // 90ns sufficient

  byte data = 0;

  for (int pin = DATA7; pin >= DATA0; pin -= 1){
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

void prestoII(byte data[], int address){
  //algorithm to programm entire UV EPROM in ca 3.5s
  Serial.println("Starting Write");
  setVpp(1); // 12,75V required

  //Byte Cycle
  for(int i = 0; i <= sizeof(data); i++){
    setAddress(address + i);
    int n = 0;
    byte vdata;

    //writeCycle
    while(1){
      //writePulse:
      setIO(0);
      digitalWrite(OE, HIGH);
      digitalWrite(CE, HIGH);

      setByte(data[i]);
      delayMicroseconds(2); // Input valid to CE low QVEL

      digitalWrite(CE, LOW);
      delayMicroseconds(100); // CE Program Pulse Width ELEH
      digitalWrite(CE, HIGH);
      delayMicroseconds(2); // CE high to Input Transition EHQX

      //verify:
      delayMicroseconds(2); // Input Transition to OE low QXGL
      digitalWrite(OE, LOW);
      setIO(1);

      delayMicroseconds(100); // OE low to Output Valid GLQV
      vdata = 0;
      for (int pin = DATA7; pin >= DATA0; pin -=1){
        vdata = (vdata << 1) + digitalRead(pin);
      }


    //verify Cycle
      if(vdata == data[i]){
        char buf[50];
        sprintf(buf, "WROTE @ %04x: %02x in %i tries", address + i, data[i], n);
        Serial.println(buf);
        break;
      }

      //if verify not successful after 25 write Cycles break
      if(n >= 25){
        char buf[50];
        sprintf(buf, "ERROR @ %04x: %02x | %02x", address + i, data[i], vdata);
        Serial.println(buf);
        break;
      }
      n++;
    }
  }
  //reset Vpp to Vcc
  setVpp(0);
  Serial.println("WRITE done");
}

void printLine(int base, byte data[16]){
  char buf[500];
  sprintf(
    buf,
    "%04x: %02x %02x %02x %02x %02x %02x %02x %02x  %02x %02x %02x %02x %02x %02x %02x %02x",
    base, 
    data[0],  data[1],  data[2],  data[3],  data[4],  data[5],  data[6],  data[7],  data[8],  data[9],  data[10], data[11], data[12], data[13], data[14], data[15]
  );

  Serial.println(buf);
}

void printContents(int len){
  Serial.println("printing Contents:");
  setIO(1);
  int chunk = 16;
  int lines = 0;
  int copy = 0;
  byte olddata[chunk];
  for(int i = 0; i < chunk; i++){olddata[i] = 0;}
  if(len == -1){len = MAXADDRESS - chunk;}

  for(int base = 0; base <= len; base += chunk){
    byte data[chunk];
    for(int i = 0; i < chunk; i++){
      data[i] = readByte(base + i);
    }

    bool doprint = 0;
    if(base == 0){
      doprint = 1;
    }
    else if(base == len){
      doprint = 1;
    }
    else{
      for(int i = 0; i < chunk; i++){
        if(data[i] != olddata[i]){
          doprint = 1; break;
        }
      }
    }

    if(doprint){
      if(copy > 0){Serial.println("  *");}
      printLine(base, data);
      copy = 0;
      lines++;
    }
    else{copy = 1;}

    if(lines > 10){
      Serial.println("  *");
      Serial.println("  *");
      Serial.println("  *");
      break;
    }
    for(int i = 0; i < chunk; i++){olddata[i] = data[i];}
  }
  Serial.println("PRINT done");
}

bool checkEPROM(byte data[], int address, bool output){
  //checks if enough Ones are present
  //Outputs missing Ones
  bool ok = 1;
  int lines = 0;
  for(int i = 0; i <= sizeof(data); i++){
    byte target = data[i];
    byte actual = readByte(address + i);
    if((target & ~(actual)) > 0){
      //imidiatly return False if check Fails and no Output required
      if(!output){return 0;}
      ok = 0;
      lines++;
      if(lines < 10){
        char buf[50];
        sprintf(buf, "One Missing @ %04x: %02x | %02x", address + i, target, actual);
        Serial.println(buf);
      }
    }
  }
  if(ok){
    Serial.println("EPROM has required Ones");
  }
  else{
    char buf[50];
    sprintf(buf, "Total %i missing Ones", lines);
    Serial.println(buf);    
  }
  return ok;
}

void setup(){
  doinit();

  //define dataset
  byte data[] = {0xff, 0xfe, 0x00, 0x12, 0xab};

  //check if EPROM has necessary Ones
  Serial.println("prepare check: type k if ready");
  while(Serial.read()!='k'){delay(100);}
  checkEPROM(data, 0x00);

  //sanity Check
  Serial.println("prepare read: type k if ready");
  while(Serial.read()!='k'){delay(100);}
  printContents(-1);
  
  //write Data
  Serial.println("prepare write: type k if ready or s to skip");
  while(1){
    char reed = Serial.read();
    if(reed == 's'){
      break;
    }
    if(reed == 'k'){
      prestoII(data, 0x00);
      break;
    }
    delay(100);
  }    

  //sanity Check
  Serial.println("prepare read: type k if ready");
  while(Serial.read()!='k'){delay(100);}
  printContents(-1);
}

void loop(){
  //Serial.println("loop");
}