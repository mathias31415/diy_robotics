
#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h" 

#include "Configuration.h"
#include "communication/WiFiConnection.hpp"
#include "communication/DataFormat.hpp"
#include "Axis.hpp"

// Initialize the display
SSD1306Wire display(0x3c, SDA, SCL);    // default: SCL : GPIO22; SDA: GPIO21

// Calls Axis constructor of Axis.hpp and passes recommended params
// look at this: Axis(int number, uint8_t stepPin, uint8_t directionPin, double gearing, int stepsPerRev, int microsteps, bool invertDirection = false)
Axis axis1(1, STEPPER_1_STEP, STEPPER_1_DIR, AXIS_1_GEARING, AXIS_1_STEPS_PER_REV, AXIS_1_MICROSTEPS, AXIS_1_POS_MIN, AXIS_1_POS_MAX, AXIS_1_VEL_MAX, AXIS_1_ACC_MAX, AXIS_1_INVERT_DIRECTION);
Axis axis2(2, STEPPER_2_STEP, STEPPER_2_DIR, AXIS_2_GEARING, AXIS_2_STEPS_PER_REV, AXIS_2_MICROSTEPS, AXIS_2_POS_MIN, AXIS_2_POS_MAX, AXIS_2_VEL_MAX, AXIS_2_ACC_MAX, AXIS_2_INVERT_DIRECTION);
Axis axis3(3, STEPPER_3_STEP, STEPPER_3_DIR, AXIS_3_GEARING, AXIS_3_STEPS_PER_REV, AXIS_3_MICROSTEPS, AXIS_3_POS_MIN, AXIS_3_POS_MAX, AXIS_3_VEL_MAX, AXIS_3_ACC_MAX, AXIS_3_INVERT_DIRECTION);
Axis axis4(4, STEPPER_4_STEP, STEPPER_4_DIR, AXIS_4_GEARING, AXIS_4_STEPS_PER_REV, AXIS_4_MICROSTEPS, AXIS_4_POS_MIN, AXIS_4_POS_MAX, AXIS_4_VEL_MAX, AXIS_4_ACC_MAX, AXIS_4_INVERT_DIRECTION);
Axis axis5(5, STEPPER_5_STEP, STEPPER_5_DIR, AXIS_5_GEARING, AXIS_5_STEPS_PER_REV, AXIS_5_MICROSTEPS, AXIS_5_POS_MIN, AXIS_5_POS_MAX, AXIS_5_VEL_MAX, AXIS_5_ACC_MAX, AXIS_5_INVERT_DIRECTION);
Axis axis6(6, STEPPER_6_STEP, STEPPER_6_DIR, AXIS_6_GEARING, AXIS_6_STEPS_PER_REV, AXIS_6_MICROSTEPS, AXIS_6_POS_MIN, AXIS_6_POS_MAX,AXIS_6_VEL_MAX, AXIS_6_ACC_MAX, AXIS_6_INVERT_DIRECTION);

bool gEnableAxis = false;     // Enable axes only when axes need to move --> otherwise off to prevent motors from overheating
bool gRobotActive = false;    // Robot active/not active --> comes from PC

void DrawDisplay(String text)
{
  // Clear display
  display.clear();

  // Text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, text);

  // Write the buffer to the display
  display.display();
}

bool onDataReceived(void *data, size_t len, void *response, size_t responseLen) 
{
  // Check if the received data has the expected size
  if (len != sizeof(Communication::PcToRobot_t)) 
  {
    Serial.println("Error: Unexpected size of received data");
    return false;
  }

  // Copy the received data into the corresponding structure
  Communication::PcToRobot_t receivedData;
  memcpy(&receivedData, data, sizeof(Communication::PcToRobot_t));
  gRobotActive  = receivedData.activate;

  // Response for PC --> since there is no feedback from robot hardware, the received data is simply sent back:
  Communication::RobotToPc_t responseData;
  responseData.messageNumber = receivedData.messageNumber + 1;
  responseData.errorCode = ErrorCode::noError;
  responseData.active = gRobotActive;
  
  if((gRobotActive == true))   // If robot is activated by PC
  {
    if(gEnableAxis && (digitalRead(HARDWARE_ENABLE) == LOW)) 
    {
      Serial.println("Hardware Enable Switch is off. Stop Motion at actual position");   // If axes are enabled and Hardware Enable Switch is LOW --> stop robot motion
      gEnableAxis = false;

      // Cancel motion at current position
      for (auto axis : Axis::axisList)
      {
        axis->moveToPosition((axis->getPosition()));    // Overwrite target position with current position if Hardware Enable Switch is turned off during motion
      }
    }
    else
    {
      // Check for each axis if the old and new axis position is the same up to 2 decimal places
      int index = 0;
      bool mustMove = false;  // If axis position is not the same --> true
      for (auto axis : Axis::axisList)
      {
        double currentPosition = axis->getPosition();
        double targetPosition = receivedData.jointSetpoints[index] * 1e-3;
        if (abs(currentPosition - targetPosition) > 0.1)     // If axis position is not the same --> move (axis positions are rounded to 2 decimal places)
        {
          mustMove = true;
          if (!gEnableAxis)   // If axes are not enabled: enable axes
          {
            digitalWrite(ENABLE_ALL, HIGH);
            gEnableAxis = true;
            Serial.println("Enable all axis");
          }

          // Check if Hardware Enable Switch is enabled
          if ((digitalRead(HARDWARE_ENABLE) == HIGH))   // if Soft and Hardware Enable HIGH --> move axis
          {
            axis->moveToPosition(receivedData.jointSetpoints[index]* 1e-3);     // Move to new axis position
          }
        }
        index++;
      }

      if (!mustMove && gEnableAxis)    // If axes do not need to move and axes are enabled --> disable axes
      {
        digitalWrite(ENABLE_ALL, LOW);
        gEnableAxis = false;
        Serial.println("Disable all axis");
      } 
    }
  }

  // Determine current axis positions for response
  int index = 0;
  for (auto axis : Axis::axisList)
  {
    responseData.jointPositions[index++] = axis->getPosition() * 1000;   // convert back to millidegrees
  }

  // Only for debugging --> remove later
  /*Serial.println("Received Data:");
  Serial.println("Active: " + String(gRobotActive));
  Serial.println("Message Number: " + String(receivedData.messageNumber));
  Serial.println("jointSetpoints[0]: " + String(responseData.jointPositions[0]));
  Serial.println("jointSetpoints[1]: " + String(responseData.jointPositions[1]));
  Serial.println("jointSetpoints[2]: " + String(responseData.jointPositions[2]));
  Serial.println("jointSetpoints[3]: " + String(responseData.jointPositions[3]));
  Serial.println("jointSetpoints[4]: " + String(responseData.jointPositions[4]));
  Serial.println("jointSetpoints[5]: " + String(responseData.jointPositions[5]));*/

  // Display output with current data
  DrawDisplay("Robot activated = " + String(gRobotActive) + " \n Enabled = " + String(digitalRead(HARDWARE_ENABLE) == HIGH)+  + " \n A1 = " + String(responseData.jointPositions[0] * 1e-3)+ "; A2 = " + String(responseData.jointPositions[1] * 1e-3)+ " \n A3 = " + String(responseData.jointPositions[2] * 1e-3)+ "; A4 = " + String(responseData.jointPositions[3] * 1e-3) + " \n A5 = " + String(responseData.jointPositions[4] * 1e-3)+ "; A6 = " + String(responseData.jointPositions[5] * 1e-3));
  
  // Copy the response into the response buffer
  memcpy(response, &responseData, sizeof(Communication::RobotToPc_t));
  return true;
}

void networkTask(void * parameter) 
{
  delay(5e3);
  DrawDisplay("Connecting to WiFi");
  WiFiConnection connection(NETWORK_SSID, NETWORK_PASSWORD, onDataReceived, 80, "ESP32_Server_Gripper");
  DrawDisplay("Connected to WiFi");
  connection.loopForever(true);
}; 
TaskHandle_t NetworkTask;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting up");

  // Initialize the display
  display.init();

  pinMode(HARDWARE_ENABLE, INPUT);    // Pin to check if hardware enable switch is on

  pinMode(ENABLE_ALL, OUTPUT);  // Enable Drivers
  digitalWrite(ENABLE_ALL, LOW);  // Disable all drivers

  // Start network task
  xTaskCreatePinnedToCore(networkTask, "networkTask", 4096*2, NULL, 17, &NetworkTask, 0);
}

void loop() {
  Axis::runAll();   // Poll all Axis -> see Axis.hpp file
}