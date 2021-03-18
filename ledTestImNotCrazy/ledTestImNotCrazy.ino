int red = 4;
int blue = 5;
int green = 6;

void setup(){

}

void loop(){
    digitalWrite(green, HIGH);
    delay(50);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
    delay(1000);
    digitalWrite(blue, LOW);
}