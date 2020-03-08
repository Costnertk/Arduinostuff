//Flashes led on board
 int ledpin = 13;

 void setup()
 {
    pinMode(ledpin, OUTPUT);
 }

 void loop()
 {
    digitalWrite(ledpin, HIGH);
    Serial.print("ON");
    delay(1000);
    digitalWrite(ledpin, LOW);
    Serial.print("OFF");
    delay(1000);
 }
