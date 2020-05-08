#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float accAngX, accAngY;

Adafruit_BME280 bme; // I2C

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 and MPU6050 test"));

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Wire.begin();
    setupMPU();
    
    Serial.println("Ready");
    delay(2000);

    Serial.println();
}

void loop() { 
    
    Serial.println("--------------------");
    Serial.println();
    Serial.print("Temperature = ");
    Serial.print(getBME('C'));
    printDegree();
    Serial.print("C ");
    Serial.print(getBME('F'));
    printDegree();
    Serial.print("F "); 
    Serial.print(getBME('K'));
    Serial.println("K ");       


    Serial.print("Pressure = ");
    Serial.print(getBME('P'));
    Serial.println(" hPa ");

    Serial.print("Humidity = ");
    Serial.print(getBME('H'));
    Serial.println("% ");
    
    Serial.print("Approx. Altitude = ");
    Serial.print(getBME('A'));
    Serial.println(" m");



    Serial.println();

    // action
    if(getBME('C') <65.2)
    {
     //digitalWrite(5, HIGH); 
    }

    recordAccelRegisters();
    recordGyroRegisters();
    calcualteRP();
    printData();

    delay(2000);
}// loop end

float getBME(char type)
{
  float value;
    float temp = bme.readTemperature();// read temperature
    float pressure = bme.readPressure() / 100.0F; // read pressure
    float rel_hum = bme.readHumidity();// read humidity
    float alt =bme.readAltitude(SEALEVELPRESSURE_HPA);// read altitude
   if(type =='F')
   {
    value = temp *9/5 + 32;//convert to Fahrenheit 
   }else if(type =='K')
   {
    value = temp + 273.15;//convert to Kelvin
   }else if(type =='H')
   {
    value = rel_hum;//return relative humidity
   }else if(type =='P')
   {
    value = pressure;//return pressure
   }else if(type =='A')
   {
    value = alt;//return approximate altitude
   }else{
    value = temp;// return Celsius
   }
   return value;
}//getBME

void printDegree()
{
    Serial.print("\xC2"); 
    Serial.print("\xB0");  
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
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

void calcualteRP() //calculates roll and pitch
{
  accAngX = (atan(accelY / sqrt(pow(accelX, 2) + pow(accelY,2))) * 180 / PI) - 0.58;
  accAngY = (atan(-1 * accelX / sqrt(pow(accelY, 2) + pow(accelZ,2))) * 180 / PI) + 1.58;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
  Serial.println("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.println(rotZ);
  Serial.println("Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.println(gForceZ);
  Serial.print("Roll = ");
  Serial.print(accAngX);
  Serial.print(" Pitch = ");
  Serial.println(accAngY);
  Serial.println();
  Serial.println("--------------------");
  Serial.println();
  Serial.println();
  
}