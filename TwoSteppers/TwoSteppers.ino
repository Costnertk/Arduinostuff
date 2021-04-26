//Works with with matlab to move stepper quickly
#include <Stepper.h>
const int stepsPerRevolution = 2052;
int rotate = 0;

Stepper myStepper1 = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper2 = Stepper(stepsPerRevolution, 2, 4, 3, 5);


void setup(){
  Serial.begin(9600);
  myStepper1.setSpeed(10);
}

void loop(){
  if(Serial.available() > 0){
    rotate = Serial.parseInt();

    if(rotate > -1000 && rotate < 1000){
        myStepper1.step(rotate);
    }
    else if(rotate >-2000 && rotate < -1000){
       rotate = rotate + 1000;
        myStepper2.step(rotate);
    }
    else if(rotate > 1000 && rotate < 2000){
        rotate = rotate - 1000;
        myStepper2.step(rotate);
    }
  }
}
