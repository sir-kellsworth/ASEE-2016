#include <Wire.h>
#include "sensorbar.h"

SensorBar bar(0x3E);
double kp=.5;
double ki=.5;
double kd=.5;

int RBaseSpeed=80;
int LBaseSpeed=50;
byte RMotor=10;
byte LMotor=11;

double error=0;
double errSum=0;
double lastError=0;
int lastTime=0;
int TARGET=B00011000;
double dErr=0;

void setup() {
  pinMode(RMotor,OUTPUT);
  pinMode(LMotor,OUTPUT);
  Serial.begin(9600);
  bar.setBarStrobe();
  bar.clearInvertBits();
  if(bar.begin()){
    Serial.print("ready");
  }else{
    Serial.print("not ready");
  }
  delay(5000);
}

void loop() {
  uint8_t raw=bar.getRaw();

  /*for(int i=0;i<7;i++){
    Serial.print(bitRead(raw,i));
  }
  Serial.println();
  delay(500);*/

  if(bitRead(raw,2)||bitRead(raw,1)||bitRead(raw,0)){
    //turn right
    analogWrite(RMotor,RBaseSpeed);
    analogWrite(LMotor,LBaseSpeed+30);
  }else if(bitRead(raw,5)||bitRead(raw,6)||bitRead(raw,7)){
    analogWrite(RMotor,RBaseSpeed+30);
    analogWrite(LMotor,LBaseSpeed);
  }else if(bitRead(raw,3)||bitRead(raw,4)){
    analogWrite(RMotor,RBaseSpeed);
    analogWrite(LMotor,LBaseSpeed);
  }

    /*unsigned long now=millis();
    unsigned long timeChange=(now-lastTime);

    error=TARGET-raw;
    errSum+=(error*timeChange);
    dErr=(error-lastError)/timeChange;

    lastError=error;  
    lastTime=now;

    //TODO figure out how to write result to motors
    double result=kp*error+ki*errSum+kd*dErr;

    int RMotorSpeed=RBaseSpeed+result;
    int LMotorSpeed=LBaseSpeed-result;

    if(RMotorSpeed>130){
      RMotorSpeed=130;
    }

    if(RMotorSpeed<50){
      RMotorSpeed=50;
    }

    if(LMotorSpeed>100){
      LMotorSpeed=100;
    }

    if(LMotorSpeed<25){
      LMotorSpeed=25;
    }
    
    analogWrite(RMotor,RMotorSpeed);
    analogWrite(LMotor,LMotorSpeed);*/

    delayMicroseconds(100);
}
