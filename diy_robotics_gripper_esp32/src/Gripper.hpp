#ifndef GRIPPER_HPP_
#define GRIPPER_HPP_

#include <ESP32Servo.h>
#include <Arduino.h>

//#include "OledDisplay.hpp"


class Gripper {
private:
  Servo myservo0;
  Servo myservo1;
  int servo0Pin;
  int servo1Pin;
  //OledDisplay display;

   
public:
  int gripperState = 0;

  Gripper()
  {
    int servo0Pin = 18;   // Default pins 12 and 19
    int servo1Pin = 19;
    myservo0.setPeriodHertz(50); // standard 50 hz servo
    myservo1.setPeriodHertz(50);
    myservo0.attach(servo0Pin, 500, 2500); // using min/max of 500us and 2500us
                                            // different servos may require different min/max settings
                                            // for an accurate 0 to 180 sweep
    myservo1.attach(servo1Pin, 500, 2500);
  };

  Gripper(int pin0, int pin1) 
  {
    int servo0Pin = pin0;
    int servo1Pin = pin1;
    myservo0.setPeriodHertz(50); // standard 50 hz servo
    myservo1.setPeriodHertz(50);
    myservo0.attach(servo0Pin, 500, 2500); // using min/max of 500us and 2500us
                                            // different servos may require different min/max settings
                                            // for an accurate 0 to 180 sweep
    myservo1.attach(servo1Pin, 500, 2500);
  };

  ~Gripper(){};


  void gripperOpen()
  {                  
    myservo0.writeMicroseconds(1750);   //  range:  500-1500 (negative turning direction, 500 = maximum torque, 1500 = torque 0)
    myservo1.writeMicroseconds(1750);   //          1500-2500 (positive turning direction, 1500 = torque 0, 2500 = maximum torque)
    delay(1500);
    myservo0.writeMicroseconds(1500);   // turn off servo
    myservo1.writeMicroseconds(1500);
    delay(500);
    Serial.println("Gripper opened");
    gripperState = 0;
  }

  void gripperClose()
  {
    myservo0.writeMicroseconds(1230);
    myservo1.writeMicroseconds(1230);
    Serial.println("Gripper closed");
    gripperState = 1;
  }

 
};

#endif
