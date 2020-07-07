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
    //ServoTest();
    CircleServo();
}

void CircleServo(){
  for(int i = 65; i <= 90; i++){
    myservoZ.write(i);
    myservoY.write(i+25);
    delay(20);
  }
  for(int i = 90; i <= 115; i++){
    myservoZ.write(i);
    myservoY.write(140-i);
    delay(20);
  }
  //for(int i = 115; i >= 65; i--){
    //myservoZ.write(i);
    //myservoY.write(180-i);
    //delay(20);
  //}
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
