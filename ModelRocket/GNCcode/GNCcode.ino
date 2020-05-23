#include <Wire.h>
#include <Servo.h>

int ledRed = 4;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float accAngX, accAngY;
float gyroDegX, gyroDegY, gyroDegZ;
float gyroZeroX, gyroZeroY, gyroZeroZ;

int minVal = 265;
int maxVal = 402;

int limit1 = 120;
int limit2 = 60;

Servo myservoZ;
Servo myservoY;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  myservoZ.attach(9);
  myservoY.attach(8);
  pinMode(ledRed, OUTPUT);
  setupMPU();
  startup();
}

void loop()
{
  recordAccelRegisters();
  recordGyroRegisters();
  //calcualteRP();
  calculateDeg();
  actuateServos();
  //printData();
  //delay(100);
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

void setupMPU() {
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
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission();
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

void calcualteRP() //calculates roll and pitch
{
  accAngX = (atan(accelY / sqrt(pow(accelX, 2) + pow(accelY, 2))) * 180 / PI) - 0.58;
  accAngY = (atan(-1 * accelX / sqrt(pow(accelY, 2) + pow(accelZ, 2))) * 180 / PI) + 1.58;
}

void calculateDeg()
{
  int xAng = map(accelX, minVal, maxVal, -90, 90);
  int yAng = map(accelY, minVal, maxVal, -90, 90);
  int zAng = map(accelZ, minVal, maxVal, -90, 90);


  gyroDegX = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  gyroDegY = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  gyroDegZ = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
}

void printData()
{
  Serial.print(" Roll = ");
  Serial.print(accAngX);
  Serial.print(" Pitch = ");
  Serial.print(accAngY);
  Serial.print(" X Angle =");
  Serial.print(gyroDegX);
  Serial.print(" Y Angle =");
  Serial.print(gyroDegY);
  Serial.print(" Z Angle =");
  Serial.println(gyroDegZ);
}

void actuateServos()
{
  if ((int)gyroDegZ <= 120 + (int)gyroZeroZ && (int)gyroDegZ >= 60 + (int)gyroZeroZ)
  {
    myservoZ.write((int)gyroDegZ);
  }
  else if (gyroDegZ > 120)
  {
    myservoZ.write(120);
  }
  else if (gyroDegZ < 60)
  {
    myservoZ.write(60);
  }

  if ((int)gyroDegY <= 120 + (int)gyroZeroY && (int)gyroDegY >= 60 + (int)gyroZeroY)
  {
    myservoY.write((int)gyroDegY);
  }
  else if (gyroDegY > 120)
  {
    myservoY.write(120);
  }
  else if (gyroDegY < 60)
  {
    myservoY.write(60);
  }
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
