#include <Arduino.h>
#include <Accelstepper.h>
#include <MultiStepper.h>

#include <Wire.h>
#include "SSD1306Wire.h" 


//Motor Pins Config
#define step1 16
#define dir1 13
#define step2  18
#define dir2 17
#define step3  5
#define dir3 19
#define step4  25
#define dir4 23
#define step5  27
#define dir5 26
#define step6  33
#define dir6 32

#define enableAll 4

// define Stepper Variables
int mshand = 16;
float sthand = 7.5;  //deg per step
float handSpeed = 1000 * mshand/sthand;
float handAcc  = 500*mshand/sthand;
int handpos = 360*mshand/sthand;

int msarm = 16;
float starm = 1.8;  //deg per step
float armSpeed = 500 * msarm/starm;
float armAcc  = 300*msarm/starm;
int armpos = 360*msarm/starm;

bool enable = false;

//init stepper objects
AccelStepper M1(AccelStepper::DRIVER, step1, dir1);
AccelStepper M2(AccelStepper::DRIVER, step2, dir2);
AccelStepper M3(AccelStepper::DRIVER, step3, dir3);
AccelStepper M4(AccelStepper::DRIVER, step4, dir4);
AccelStepper M5(AccelStepper::DRIVER, step5, dir5);
AccelStepper M6(AccelStepper::DRIVER, step6, dir6);


// Initialize the display
SSD1306Wire display(0x3c, SDA, SCL);;    // default: SCL : GPIO22; SDA: GPIO21

void setup() {
  Serial.begin(115200);

  // Initialize the display
  display.init();
  // display.flipScreenVertically();

  pinMode(enableAll, OUTPUT);

  pinMode(step1, OUTPUT);
  pinMode(dir1, OUTPUT);
  M1.setMaxSpeed(armSpeed);
  M1.setAcceleration(armAcc);

  pinMode(step2, OUTPUT);
  pinMode(dir2, OUTPUT);
  M2.setMaxSpeed(armSpeed);
  M2.setAcceleration(armAcc);

  pinMode(step3, OUTPUT);
  pinMode(dir3, OUTPUT);
  M3.setMaxSpeed(armSpeed);
  M3.setAcceleration(armAcc);

  pinMode(step4, OUTPUT);
  pinMode(dir4, OUTPUT);
  M4.setMaxSpeed(handSpeed);
  M4.setAcceleration(handAcc);

  pinMode(step5, OUTPUT);
  pinMode(dir5, OUTPUT);
  M5.setMaxSpeed(handSpeed);
  M5.setAcceleration(handAcc);

  pinMode(step6, OUTPUT);
  pinMode(dir6, OUTPUT);
  M6.setMaxSpeed(handSpeed);  
  M6.setAcceleration(handAcc); 

  
}

void DrawStateDisplay(String text)
{
    // clear the display
    display.clear();

    // Text
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, text);

    // write the buffer to the display
    display.display();
}

void loop() {
  M1.run();
  M2.run();
  M3.run();
  M4.run();
  M5.run();
  M6.run();

  //Serial.println(enable);

  while(Serial.available() > 0){
    byte task = Serial.read();

    switch(task){
      case 'q':
        M1.move(-armpos);
        Serial.println("M1 forward");
        DrawStateDisplay("M1 forward");
        break;
      case 'a':
        M1.move(armpos);
        Serial.println("M1 reverse");
        DrawStateDisplay("M1 reverse");
        break;
      case 'w':
        M2.move(armpos);
        Serial.println("M2 forward");
        DrawStateDisplay("M2 forward");
        break;
      case 's':
        M2.move(-armpos);
        Serial.println("M2 reverse");
        DrawStateDisplay("M2 reverse");
        break;
      case 'e':
        M3.move(-armpos);
        Serial.println("M3 forward");
        DrawStateDisplay("M3 forward");
        break;
      case 'd':
        M3.move(armpos);
        Serial.println("M3 reverse");
        DrawStateDisplay("M3 reverse");
        break;
      case 'r':
        M4.move(-handpos);
        Serial.println("M4 forward");
        DrawStateDisplay("M4 forward");
        break;
      case 'f':
        M4.move(handpos);
        Serial.println("M4 reverse");
        DrawStateDisplay("M4 reverse");
        break;
      case 't':
        M5.move(handpos);
        Serial.println("M5 forward");
        DrawStateDisplay("M5 forward");
        break;
      case 'g':
        M5.move(-handpos);
        Serial.println("M5 reverse");
        DrawStateDisplay("M5 reverse");
        break;
      case 'z':
        M6.move(-handpos);
        Serial.println("M6 forward");
        DrawStateDisplay("M6 forward");
        break;
      case 'h':  
        M6.move(handpos);
        Serial.println("M6 reverse");
        DrawStateDisplay("M6 reverse");
        break;  
      case 'n':
        digitalWrite(enableAll, HIGH);
        Serial.println("Enable all Axis");
        DrawStateDisplay("Enable all Axis");
        enable = true;
        break;
      case 'm':
        digitalWrite(enableAll, LOW);
        Serial.println("Disable all Axis");
        DrawStateDisplay("Disable all Axis");
        enable = false;
        break;
    }
   }



}
