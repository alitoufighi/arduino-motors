#include <SoftwareSerial.h>
#include <Stepper.h>
#define STEP_ANGLE 10
#define STEPS 360/STEP_ANGLE
#define clockwiseButton A0
#define antiClockwiseButton A1
#define pauseButton A2

SoftwareSerial vSerial(12, 13);
Stepper stepper(STEPS, 8, 9, 10, 11);

int step;

void setup() {
  stepper.setSpeed(6);
  pinMode(clockwiseButton, INPUT);
  pinMode(antiClockwiseButton, INPUT);
  pinMode(pauseButton, INPUT);

  step = 1;
}

void loop() {
  if(digitalRead(clockwiseButton) == HIGH){
    vSerial.println("Clockwise");
    step = 1;
  }
  while(digitalRead(clockwiseButton) == HIGH);
  
  if(digitalRead(antiClockwiseButton) == HIGH){
    vSerial.println("Anti Clockwise");
    step = -1;
  }
  while(digitalRead(antiClockwiseButton) == HIGH);

  if(digitalRead(pauseButton) == HIGH){
    vSerial.println("Paused");
    step = 0;
  }
  while(digitalRead(pauseButton) == HIGH);

  stepper.step(step);
  delay(20);
}
