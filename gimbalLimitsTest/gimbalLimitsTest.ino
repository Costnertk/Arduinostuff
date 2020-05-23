#include <Servo.h>

Servo myservoZ;
Servo myservoY;

int limit1 = 120;
int limit2 = 60;

void setup() {
  Serial.begin(9600);
  myservoZ.attach(9);
  myservoY.attach(8);
}

void loop()
{
    ServoTest();
}

void ServoTest(){
  myservoZ.write(limit1);
  Serial.println(limit1);
  delay(200);
  myservoZ.write(90);
  Serial.println("90");
  delay(200);
  myservoZ.write(limit2);
  Serial.println(limit2);
  delay(200);
  myservoZ.write(90);
  Serial.println("90");
  delay(200);
  myservoY.write(limit1);
  Serial.println(limit1);
  delay(200);
  myservoY.write(90);
  Serial.println("90");
  delay(200);
  myservoY.write(limit2);
  Serial.print(limit2);
  delay(200);
  myservoY.write(90);
  Serial.println("90");
  delay(200);
}
