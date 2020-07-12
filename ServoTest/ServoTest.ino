#include <Servo.h>

Servo myservoZ;
Servo myservoY;

int wait = 10;

void setup(){
    Serial.begin(9600);
    myservoZ.attach(9);
    myservoY.attach(8);
}

void loop(){
    //ServoTest();
    CircleServo();
    //SquareServo();
}

void SquareServo(){
  myservoZ.write(65);
  myservoY.write(65);
  delay(200);
  myservoZ.write(115);
  delay(200);
  myservoY.write(115);
  delay(200);
  myservoZ.write(65);
  delay(200);
}

void CircleServo(){
  for(int i = 65; i <= 90; i++){
    myservoZ.write(i);
    myservoY.write(i+25);
    delay(wait);
  }
  
  for(int i = 90; i <= 115; i++){
    myservoZ.write(i);
    myservoY.write(abs(i-205));
    delay(wait);
  }

  for(int i = 115; i >= 90; i--){
    myservoZ.write(i);
    myservoY.write(i-25);
    delay(wait);
  }

  for(int i = 90; i >= 65; i--){
    myservoZ.write(i);
    myservoY.write(abs(i-155));
    delay(wait);
  }
  
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
