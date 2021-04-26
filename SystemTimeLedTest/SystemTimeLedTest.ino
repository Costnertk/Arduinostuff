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
<<<<<<< HEAD
    //currentSysTime = millis();
    //ledFlash();
    standby();
=======
    currentSysTime = millis();
    ledFlash();
>>>>>>> eb928c05d52a85e094ab2124413f7fd4f2e572b1
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
