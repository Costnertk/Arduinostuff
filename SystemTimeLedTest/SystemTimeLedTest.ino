//testing using millis() to control system functions with system clock

int red = 4;
int blue = 5;
int green = 6;

void setup(){
    Serial.begin(9600);
}

void loop(){
    ledFlash();
}

void ledFlash(){
    if((millis()%50)==0){
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
    }
    if((millis()%60)==0){
        digitalWrite(green, LOW);
        digitalWrite(blue, HIGH);
    }
}