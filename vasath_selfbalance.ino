#include <Servo.h>
Servo myservo;

#define SOUND_VELOCITY 0.034

const int trigPin = D6;
const int echoPin = D7;
// int st=0;
long duration;
float distanceCm;
float distanceInch;

int pos;
char bt;

void setup() {
 Serial.begin(9600);
 myservo.attach(2);
 pinMode(D1,OUTPUT);
 pinMode(D2,OUTPUT);
 pinMode(D5,INPUT);
//  pinMode(8,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
 digitalWrite(D1,LOW);
 digitalWrite(D2,LOW);
//  digitalWrite(6,HIGH);
//  digitalWrite(7,HIGH);
//  digitalWrite(8,HIGH);
}
void loop() {
  Serial.println(digitalRead(D5));
  if(digitalRead(D5)==HIGH){
      if(Serial.available()>0)
      {
        bt=Serial.read();
        Serial.println(bt);
      }
      if((bt=='F'))
      {
        digitalWrite(D1,HIGH);
        digitalWrite(D2,LOW);
      }
      if((bt=='B'))
      {
        digitalWrite(D1,LOW);
        digitalWrite(D2,HIGH);
      }

      if((bt=='S'))
      {
        digitalWrite(D1,LOW);
        digitalWrite(D2,LOW);
      }

      if((bt=='R'))
      {
        int p;
        for (p = pos; p <= 180; p += 3) {
          myservo.write(p);
          Serial.println(p);
          bt=Serial.read();
          if((bt=='S')||(p==180)||(p>180)){
            pos=p;
            break;
          }
        }
      }

      if((bt=='L'))
      {
        int p;
        for (p=pos; p >= 0; p -= 3) {
          myservo.write(p);
          Serial.println(p);
          bt=Serial.read();
          if((bt=='S')||(p==0)||(p<0)){
            pos=p;
            break;
          }
        }
      }
  }
  else
  {
    // myservo.write(pos);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration * SOUND_VELOCITY/2;
    Serial.println(distanceCm);
    // if(st==1){
    //   delay(1000);
    //   myservo.write(90);
    // }
    if(distanceCm < 15 && distanceCm > 1){
      // myservo.write(40);
      digitalWrite(D1,LOW);
      digitalWrite(D2,LOW);
      // st=1;
      // digitalWrite(D1,LOW);
      // digitalWrite(D2,HIGH);
      // digitalWrite(D1,LOW);
      // digitalWrite(D2,LOW);
    }
    else{
      digitalWrite(D1,HIGH);
      digitalWrite(D2,LOW);
      // st=0;
    }
    if(Serial.available()>0){
        bt=Serial.read();
        Serial.println(bt);
        if((bt=='R'))
        {
          int p;
           for (p = pos; p <= 180; p += 3) {
            myservo.write(p);
            Serial.println(p);
            bt=Serial.read();
            if((bt=='S')||(p==180)||(p>180)){
              pos=p;
              break;
            }
          }
        }

        if((bt=='L'))
        {
          int p;
          for (p=pos; p >= 0; p -= 3) {
            myservo.write(p);
            Serial.println(p);
            bt=Serial.read();
            if((bt=='S')||(p==0)||(p<0)){
              pos=p;
              break;
            }
          }
        }
      }
  }
}