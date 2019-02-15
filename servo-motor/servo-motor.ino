#define clockwiseButton A0
#define antiClockwiseButton A1
#include <SoftwareSerial.h>
#include <Servo.h>
#define servoPin 6

SoftwareSerial vSerial(12, 13);
Servo myservo;

int pos;

void setup() {
  pos = 90;
  vSerial.begin(9600);
  myservo.attach(servoPin);
  pinMode(clockwiseButton, INPUT);
  pinMode(antiClockwiseButton, INPUT);
  myservo.write(pos);
}

void loop() {
  if(digitalRead(clockwiseButton) == HIGH){
    vSerial.println("Clockwise");
    pos += 4;
    pos = pos % 180;
    myservo.write(pos);
  }
  while(digitalRead(clockwiseButton) == HIGH);
  
  if(digitalRead(antiClockwiseButton) == HIGH){
    vSerial.println("Anti Clockwise");
    pos -= 4;
    pos = pos % 180;
    myservo.write(pos);
  }
  while(digitalRead(antiClockwiseButton) == HIGH);
  
  delay(20);
}
