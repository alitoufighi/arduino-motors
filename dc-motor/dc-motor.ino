#define pauseButton A0
#define rotButton A1
#define decButton A2
#define incButton A3
#include <SoftwareSerial.h>
SoftwareSerial vSerial(12, 13);

#define CLOCKWISE false
#define ANTICLOCKWISE true

bool dir;
bool paused;

int en = 10;
int in1 = 6;
int in2 = 7;

int speed1;
int speed2;
int speed;

int lastSpeed;
int lastSpeed1;
int lastSpeed2;

void setup() {
  vSerial.begin(9600);
  // put your setup code here, to run once:
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(rotButton, INPUT);
  pinMode(pauseButton, INPUT);
  pinMode(decButton, INPUT);
  pinMode(incButton, INPUT);

  speed1 = 255;
  speed2 = 0;
  speed = 255;
  analogWrite(en, 255);

  paused = false;
  dir = CLOCKWISE;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(rotButton) == HIGH) {
      vSerial.println("Clicked");
      dir = !dir;
  }
  while(digitalRead(rotButton) == HIGH);


  if(digitalRead(pauseButton) == HIGH) {
    paused = !paused;
    if(paused == true) {
      lastSpeed = speed;
      speed = 0;
    } else
      speed = lastSpeed;
  }
  while(digitalRead(pauseButton) == HIGH);


  if(digitalRead(incButton) == HIGH) {
    speed += 10;
    if(speed > 255)
      speed -= 10;speed2 -= 10;
  }
  while(digitalRead(incButton) == HIGH);

  if(digitalRead(decButton) == HIGH) {  
    speed -= 10;
    if(speed < 0)
      speed = 0;
  }
  while(digitalRead(decButton) == HIGH);

  
  delay(20);
  if(dir == CLOCKWISE) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } 
  analogWrite(en, speed);
}
