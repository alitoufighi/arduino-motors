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
      vSerial.print("Changing Rotate Direction From ");
      if(dir == CLOCKWISE)
        vSerial.println("Clockwise to Anti-Clockwise");
      else
        vSerial.println("Anti-Clockwise to Clockwise");
      dir = !dir;
  }
  while(digitalRead(rotButton) == HIGH);

  if(digitalRead(pauseButton) == HIGH) {
    paused = !paused;
    if(paused == true) {
      vSerial.println("Paused");
      lastSpeed = speed;
      speed = 0;
    } else {
      vSerial.println("Resumed");
      speed = lastSpeed;
    }
  }
  while(digitalRead(pauseButton) == HIGH);

  if(digitalRead(incButton) == HIGH) {
    vSerial.print("Increase speed from ");
    vSerial.print(speed);
    speed += 10;
    if(speed > 255)
      speed -= 10;
    vSerial.print(" to ");
    vSerial.println(speed);
  }
  while(digitalRead(incButton) == HIGH);

  if(digitalRead(decButton) == HIGH) {
    vSerial.print("Decrease speed from ");
    vSerial.print(speed);
    speed -= 10;
    if(speed < 0)
      speed = 0;
    vSerial.print(" to ");
    vSerial.println(speed);
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
