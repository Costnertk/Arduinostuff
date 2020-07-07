#include <Servo.h>

Servo myservoZ;
Servo myservoY;
int wait = 100;
void setup(){
    Serial.begin(9600);
    myservoZ.attach(9);
    myservoY.attach(8);
}

void loop(){
    ServoTest();
}

void ServoTest(){
  myservoZ.write(115);
  delay(wait);
  myservoZ.write(90);
  delay(wait);
  myservoZ.write(65);
  delay(wait);
  myservoZ.write(90);
  delay(wait);
  myservoY.write(115);
  delay(wait);
  myservoY.write(90);
  delay(wait);
  myservoY.write(65);
  delay(wait);
  myservoY.write(90);
  delay(wait);
} 
