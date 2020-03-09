//button turns on led

int ledpin = 13;
int buttonpin = 3;

void setup()
{
    Serial.begin(9600);
    pinMode(ledpin, OUTPUT);
    pinMode(buttonpin, INPUT);
}

void loop()
{
    if(digialRead(buttonpin) == HIGH)
    {
        digitalWrite(ledpin, HIGH);
        Serial.print("button pushed");
    }
    else
    {
        digitalWrite(ledpin, LOW);
    }
    
}