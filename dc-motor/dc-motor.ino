#include <SoftwareSerial.h>
#define pauseButton A0
#define rotButton A1
#define decButton A2
#define incButton A3
#define CLOCKWISE false
#define ANTICLOCKWISE true
#define en 10
#define in1 6
#define in2 7

bool dir;
bool paused;

int speed;
int lastSpeed;

SoftwareSerial vSerial(12, 13);

void setup() {
  vSerial.begin(9600);
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(rotButton, INPUT);
  pinMode(pauseButton, INPUT);
  pinMode(decButton, INPUT);
  pinMode(incButton, INPUT);

  speed = 255;
  paused = false;
  dir = CLOCKWISE;
  
  analogWrite(en, speed);
}

void loop() {
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
      speed -= 10;
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
