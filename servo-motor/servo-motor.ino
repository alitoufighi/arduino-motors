#define clockwiseButton A0
#define antiClockwiseButton A1
#include <SoftwareSerial.h>
#include <Servo.h>
#define servoPin 6

SoftwareSerial vSerial(12, 13);
Servo servo;  // our servo motor has range -180 and +180.

int pos;

void setup() {
  pos = 90;
  vSerial.begin(9600);
  servo.attach(servoPin);
  pinMode(clockwiseButton, INPUT);
  pinMode(antiClockwiseButton, INPUT);
  servo.write(pos);
}

void loop() {
  if(digitalRead(clockwiseButton) == HIGH){
    vSerial.println("Clockwise");
    pos += 1;
    pos = pos % 180;
    servo.write(pos);
  }
  while(digitalRead(clockwiseButton) == HIGH);
  
  if(digitalRead(antiClockwiseButton) == HIGH){
    vSerial.println("Anti Clockwise");
    pos -= 1;
    pos = pos % 180;
    servo.write(pos);
  }
  while(digitalRead(antiClockwiseButton) == HIGH);
  
  delay(20);
}
