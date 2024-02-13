#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h" 

#include "Gripper.hpp"


// Global Parameters for Gripper
int servo0Pin = 18;
int servo1Pin = 19;
Gripper myGripper(servo0Pin, servo1Pin);


// Initialize the Display
SSD1306Wire display(0x3c, SDA, SCL);    // default: SCL : GPIO22; SDA: GPIO21


void DrawDisplay(String text)
{
  // Clear display
  display.clear();

  // Text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, text);

  // Write the buffer to the display
  display.display();
}

void gripperControl(int command)
{
  DrawDisplay("Received\nsetGripper to \n" + String(command) + " from Serial");

  if ((command == 0) && (myGripper.gripperState == 1)) // Open Gripper
  {
    myGripper.gripperOpen();
  }
  else if ((command == 1) && (myGripper.gripperState == 0)) // Close Gripper
  {
    myGripper.gripperClose();
  }
}


void setup() 
{
  Serial.begin(115200);

  // Initialize the Display
  display.init();
  display.flipScreenVertically();
}

void loop() 
{
  if (Serial.available() > 0)
  {
    int command = Serial.parseInt();
    if (command >= 0 && command <= 1)
    {
      gripperControl(command);

      // Display current gripper state
      DrawDisplay("Gripper State: " + String(myGripper.gripperState));
    }
    else
    {
      Serial.println("Invalid input. Please enter 0 or 1.");
    }
  }
}