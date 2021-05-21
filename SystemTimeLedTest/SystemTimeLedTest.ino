//testing using millis() to control system functions with system clock

int red = 4;
int blue = 5;
int green = 6;
int currentSysTime, ledOffSysTime;

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
        ledOffSysTime = millis() + 100;
        digitalWrite(green, LOW);
        digitalWrite(blue,HIGH);
    }

    if(currentSysTime==ledOffSysTime){
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
    }
}

void standby(){
  digitalWrite(green, HIGH);
  delay(50);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(blue, LOW);
}
