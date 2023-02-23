#include <Arduino.h>
#include <Servo.h>

const int r = 9;
const int g = 10;
const int b = 11;
const int servoPin = 6;
const int temperaturaPin = A0;

float valorSensor, tensaoSaida, temperatura;

Servo s;

int myArray[2];
byte* ddata = reinterpret_cast<byte*>(&myArray);
int pcDataLen = sizeof(myArray);
bool newData = false;

void checkForNewData() {
  if (Serial.available() >= pcDataLen && newData == false) {
    for (byte n = 0; n < pcDataLen; n++) {
      ddata[n] = Serial.read();
    }
    while (Serial.available() > 0) {
      Serial.read();
    }
    newData = true;
  }
}

void setup(){
  Serial.begin(115200);
  s.attach(servoPin);
  s.write(0);
  pinMode(temperaturaPin, INPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  analogWrite(r, 0);
  analogWrite(g, 0);
  analogWrite(b, 0);
}

void loop(){

  checkForNewData();

  if (newData == true) {
    if(ddata[0] == 0){
      analogWrite(r, ddata[1]);
      analogWrite(g, ddata[2]);
      analogWrite(b, ddata[3]);
    } else if(ddata[0] == 1){
      valorSensor = analogRead(temperaturaPin);
      temperatura = (valorSensor * 500) / 1024;
      Serial.println(String(temperatura));
    } else if(ddata[0] == 2){
      if(ddata[1] >= 0 && ddata[1] <= 180){
        s.write(ddata[1]);
      }
    }
    
    newData = false;
  }
}