//Flashes led on board
 int ledpin = 13;

 void setup()
 {
   Serial.begin(9600);
   pinMode(ledpin, OUTPUT);
 }

 void loop()
 {
   digitalWrite(ledpin, HIGH);
   Serial.println("ON");
   delay(30);
   digitalWrite(ledpin, LOW);
   Serial.println("OFF");
   delay(500);
 }
