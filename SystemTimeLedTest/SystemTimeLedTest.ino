//testing using millis() to control system functions with system clock

int red = 4;
int blue = 5;
int green = 6;

int currentSysTime;
int ledOffSysTime;

void setup(){
    Serial.begin(9600);
}

void loop(){
    currentSysTime = millis();
    ledFlash();
}

void ledFlash(){
    if((currentSysTime%2000)==0){
        int ledOffSysTime = millis() + 500;
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
    }
    if(currentSysTime==ledOffSysTime){
        digitalWrite(green, LOW);
        digitalWrite(blue,HIGH);
    }
}