// intended for use with emostate_serial.py





const byte numStatus = 15;
byte ledPin[1] =  {13};
// Values sent over serial to Arduino.
float time;
float userID;
float wirelessSigStatus;
float Blink;
float leftWink;
float rightWink;
float surprise = 0.0;
float frown;
float clench;
float smile;
float longExcitement;
float shortExcitement;
float boredom;
float mentalCommandAction;
float mentalCommandPower;

const byte buffSize = 132;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;

char messageFromPC[buffSize] = {0};

unsigned long curMillis;

unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;
int blink_rate = 0;

//=============

void setup() {
  Serial.begin(9600);

    // flash LEDs so we know we are alive
  for (byte n = 0; n < numStatus; n++) {
     pinMode(ledPin[n], OUTPUT);
     digitalWrite(ledPin[n], HIGH);
  }
  delay(500); // delay() is OK in setup as it only happens once

  for (byte n = 0; n < numStatus; n++) {
     digitalWrite(ledPin[n], LOW);
  }
    // tell the PC we are ready
  Serial.println("<Arduino is ready>");
}

//=============

void loop() {
  curMillis = millis();
  getDataFromPC();
  replyToPC();
  blinkLEDs();

}

//=============

void getDataFromPC() {

    // receive data from PC and save it into inputBuffer

  if(Serial.available() > 0) {

    char x = Serial.read();

      // the order of these IF clauses is significant

    if (x == endMarker) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }

    if(readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }

    if (x == startMarker) {
      bytesRecvd = 0;
      readInProgress = true;
    }
  }
}

//=============

void parseData() {

    // split the data into its parts
    // assumes the data will be received as (eg) 0,1,35

  char * strtokIndx; // this is used by strtok() as an index
  //Serial.println('hello');
  //Serial.println(inputBuffer);

  strtokIndx = strtok(inputBuffer,","); // get the first part
  time = atof(strtokIndx); //  convert to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  userID = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  wirelessSigStatus = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  Blink = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  leftWink = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  rightWink = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  surprise = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  frown = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  clench = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  smile = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  longExcitement = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  shortExcitement = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  boredom = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mentalCommandAction = atof(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mentalCommandPower = atof(strtokIndx);


}

//=============

void replyToPC() {

  if (newDataFromPC) {
    newDataFromPC = false;
    Serial.print("<Time ");
    Serial.print(time);
    Serial.print(" UserID ");
    Serial.print(userID);
    Serial.print(" wirelessSigStatus ");
    Serial.print(wirelessSigStatus);
    Serial.print(" Blink ");
    Serial.print(Blink);
    Serial.print(" leftWink ");
    Serial.print(leftWink);
    Serial.print(" rightWink ");
    Serial.print(rightWink);
    Serial.print(" Surprise ");
    Serial.print(surprise);
    Serial.print(" Frown ");
    Serial.print(frown);
    Serial.print(" Clench ");
    Serial.print(clench);
    Serial.print(" Smile ");
    Serial.print(smile);
    Serial.print(" longExcitement ");
    Serial.print(longExcitement);
    Serial.print(" shortExcitement ");
    Serial.print(shortExcitement);
    Serial.print(" Boredom ");
    Serial.print(boredom);
    Serial.print(" MentalCommand Action ");
    Serial.print(mentalCommandAction);
    Serial.print(" MentalCommand Power ");
    Serial.print(mentalCommandPower);
    Serial.println(">");
  }
}

void blinkLEDs() {
  if (Blink == 1) {
    blink_rate = 100;
    digitalWrite(ledPin[0], HIGH);
    delay(blink_rate);
    digitalWrite(ledPin[0], LOW);
    delay(blink_rate);
  }
  blink_rate = Blink * 100;
  digitalWrite(ledPin[0], HIGH);
  delay(blink_rate);
  digitalWrite(ledPin[0], LOW);
  delay(blink_rate);

}