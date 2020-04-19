#include <Wire.h>
#include <Servo.h>

int ledRed = 4;
int ledGreen = 5;
int ledBlue = 6;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float gyroDegX, gyroDegY, gyroDegZ;
float gyroZeroX, gyroZeroY, gyroZeroZ;

int minVal = 265;
int maxVal = 402;

Servo myservoZ;
Servo myservoY;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  myservoZ.attach(9);
  myservoY.attach(8);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  setupMPU();
  startup();
}

void loop() {
  standby();
}

void startup() {
  digitalWrite(ledRed, HIGH);
  
  for (int i = 0; i < 10; i++) {
    recordGyroRegisters();
    calculateDeg();
    gyroZeroX += gyroDegX;
    gyroZeroY += gyroDegY;
    gyroZeroZ += gyroDegZ;
    delay(500);
  }

  gyroZeroX /= 10;
  gyroZeroY /= 10;
  gyroZeroZ /= 10;

  ServoTest();
  digitalWrite(ledRed, LOW);
}

void standby(){
  digitalWrite(ledGreen, HIGH);
  delay(50);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, HIGH);
  delay(1000);
  digitalWrite(ledBlue, LOW);
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)                                                                                               
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Accel Registers (3B - 40)
  while (Wire.available() < 6);
  accelX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData() {
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6);
  gyroX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}

void calculateDeg() {
  int xAng = map(accelX, minVal, maxVal, -90, 90);
  int yAng = map(accelY, minVal, maxVal, -90, 90);
  int zAng = map(accelZ, minVal, maxVal, -90, 90);


  gyroDegX = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  gyroDegY = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  gyroDegZ = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
}

void ServoTest(){
  myservoZ.write(180);
  delay(200);
  myservoZ.write(90);
  delay(200);
  myservoZ.write(0);
  delay(200);
  myservoZ.write(90);
  delay(200);
  myservoY.write(180);
  delay(200);
  myservoY.write(90);
  delay(200);
  myservoY.write(0);
  delay(200);
  myservoY.write(90);
}
