#include "dht.h"
dht DHT;
#define DHT11_PIN 12  //pin 12 for 

int ledPin = 13;
int soil = A0;
int light = A2;

const int stepPinx = 3;
const int dirPinx = 4;
const int stepPiny = 5;
const int dirPiny = 6;
const int stepPinz = 7;

const int dirPinz = 8;
int motor = 2;
String b;
int x, y, xa = 0, ya = 0;
long sfx = 36500, sfy = 37500, sfz = 20000;
int left = 0, right = 1, zup = 1, zdown = 0;
int up = 1, down = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(stepPinx, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(dirPinx, OUTPUT);
  pinMode(stepPiny, OUTPUT);
  pinMode(dirPiny, OUTPUT);
  pinMode(stepPinz, OUTPUT);
  pinMode(dirPinz, OUTPUT);
  pinMode(soil, INPUT);
  pinMode(A5, INPUT);
  pinMode(motor, OUTPUT);
  digitalWrite(motor, HIGH);
}

void loop() {
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):
    b = Serial.readString();
    // set the brightness of the LED:
    if (b == "1")
      digitalWrite(ledPin, HIGH);
    else {
      if (b == "checkHumidity")

        checkHum();
      else {
        if (b == "checkTemperature")

          checkTemp();
        else {
          if (b == "checkSun") {
            int m;
            Serial.println(45);
            //m = analogRead(A5);
            //m = map(l, 0, 1024, 100, 0);
            //Serial.print(analogRead(A5));
          }
          else {
            if (b == "moveTo") {
              moveTo();
            } else {
              if (b == "moveToOrigin") {
                moveToOrigin();
              }
            }
          }
        }
      }
    }
  }
}

void checkHum() {
  //Serial.println(20);

  int d = DHT.read11(DHT11_PIN);
  //Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
}
void checkTemp() {
  //Serial.println(15);

  int d = DHT.read11(DHT11_PIN);
  //Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
}
//void checkSun() {

//}
void moveTo() {

  while (true) {
    if (Serial.available()) {
      b = Serial.readString();
      x = b.toInt();
      //      Serial.println(x);
      Serial.println(x);

      break;
    }
  }
  while (true) {
    if (Serial.available()) {
      b = Serial.readString();
      y = b.toInt();
      Serial.println(y);
      break;
    }
  }
  moveHead();
  checkAndWater();
  Serial.println("Done");
  return;
}

void moveHead() {
  //  Serial.println(xa);
  //  Serial.println(ya);
  //  Serial.println(x);
  //  Serial.println(y);
  if (x == 1 && y == 1 ) {
    xa = x; ya = y;
    //Serial.print("move x1");//move both x to top and y to right(may be if needed)
    moveX(6000, up);
    //Serial.print("move xx");
  } else {
    if (xa == x && ya < y) {
      ya = y;                     //move y only to left
      moveY(sfy, left);
    } else {
      if (xa < x && ya == y) {
        xa = x;                  // move x only to top
        moveX(sfx, up);
      } else {
        if (xa == x && ya > y) {
          ya = y;                // move y only to right
          moveY(sfy, right);
        }
      }
    }
  }
  return;
}

void moveX(long xx, int dir) {
  //Serial.println("move x");
  digitalWrite(dirPinx, dir); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for (long k = 0; k < xx; k++) {
    //Serial.println(k);
    digitalWrite(stepPinx, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinx, LOW);
    delayMicroseconds(500);
  }
  //Serial.println("move x");
  return;
}
void moveY(long yy, int dir) {
  //Serial.println("move y");
  digitalWrite(dirPiny, dir); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for (long k = 0; k < yy; k++) {
    //Serial.println(k);
    digitalWrite(stepPiny, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPiny, LOW);
    delayMicroseconds(500);
  }
  //Serial.println("move y");
  return;
}

void moveZ(long zz, int dir) {
  //Serial.println("move z");
  digitalWrite(dirPinz, dir); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for (long k = 0; k < zz; k++) {
    //Serial.println(k);
    digitalWrite(stepPinz, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinz, LOW);
    delayMicroseconds(500);
  }
  //Serial.println("move z");
  return;
}

void moveToOrigin() {
  moveX(2 * sfx, down);
  moveX(6000, down);
  moveY(2 * sfy, right);
  xa = 0;
  ya = 0;
  Serial.println("Done");
}

void checkAndWater() {
  moveZ(sfz, zdown);
  checkSoil();
  moveZ(sfz, zup);
}

void checkSoil() {
  delay(1000);
  int ll, mm;
  ll = analogRead(A1);
  mm = map(ll, 0, 1024, 100, 0);
  Serial.println(mm);
  if (mm < 25) {
    //water();
    digitalWrite(motor, LOW);
    delay(2500);
    Serial.println(mm);
    digitalWrite(motor, HIGH);
  } else {
    delay(2000);
    Serial.println(mm);
  }
}

void water() {
  int l, m;
  while (true) {
    digitalWrite(motor, LOW);
    delay(2500);
    l = analogRead(A1);
    m = map(l, 0, 1024, 100, 0);
    Serial.println(m);
    //if (m > 0) {
    //delay(100);
    break;
    //}
  }
  digitalWrite(motor, HIGH);
}
