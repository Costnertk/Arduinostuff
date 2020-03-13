#include <Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float accAngX, accAngY;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
}

