#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("BME280 Test");
    delay(2000);

    Serial.println();
}

void loop() { 
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