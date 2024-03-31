#include <RH_ASK.h>

RH_ASK driver;


const int motorPin1 = 7;  // Pin 7 of L293D
const int motorPin2 = 8;  // Pin 8 of L293D
const int motorPin3 = 9; // Pin 9 of L293D
const int motorPin4 = 10; // Pin 10 of L293D
const int voltpin = 13;

void setup()
{
    Serial.begin(9600); 
    if (!driver.init())
         Serial.println("no radio");
}

#define BUFSIZE 10

void moveForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  //Serial.println("Forward");
}

void moveBackward() { 
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  //Serial.println("Backward");
}

void turnRight() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  //Serial.println("Left");
}

void turnLeft() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  //Serial.println("Right");
}

void stop() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  //Serial.println("Stop");
}



void loop()
{
    uint8_t buf[BUFSIZE];
    uint8_t buflen;

    buflen = BUFSIZE;
    if (driver.recv(buf, &buflen)) 
    {
      Serial.print("Received "); Serial.print(buflen,DEC); Serial.write(" bytes:  ");
      buf[buflen]=0;
      Serial.println((char*)buf);         
    }
    String ch = buf;
    if (ch == "f" ) {
        moveForward();
      } else if (ch == "b") {
        moveBackward();
      } else if (ch == "l") {
        turnLeft();
      } else if (ch == "r") {
        turnRight();
      } else if (ch == "s") {
        stop();
      }
    else {
      Serial.println("false");
    }
}


