#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h" 

#include "Configuration.h"
#include "communication/WiFiConnection.hpp"
#include "communication/DataFormat.hpp"
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

  Serial.println("Received Data:");
  //Serial.println("Enable Power: " + String(receivedData.enablePower));
  Serial.println("Message Number: " + String(receivedData.messageNumber));
  Serial.println("setGripper: " + String(receivedData.setGripper));
  DrawDisplay("Received\nsetGripper to \n" + String(receivedData.setGripper) + " from PC");
  
  if((receivedData.setGripper == 0) && (myGripper.gripperState == 1))       // Open Gripper
  {
    myGripper.gripperOpen();
  }

  else if((receivedData.setGripper == 1) && (myGripper.gripperState == 0))       // Close Gripper
  {
    myGripper.gripperClose();
  }

  // Response for PC:
  Communication::RobotToPc_t responseData;
  responseData.messageNumber = receivedData.messageNumber + 1;
  responseData.errorCode = ErrorCode::noError;
  responseData.gripperState = myGripper.gripperState;

  // Copy the response into the response buffer
  memcpy(response, &responseData, sizeof(Communication::RobotToPc_t));
  return true;
}


void networkTask(void * parameter) 
{
  delay(5e3);
  DrawDisplay("Connecting\n to WiFi");
  WiFiConnection connection(NETWORK_SSID, NETWORK_PASSWORD, onDataReceived, 80, "ESP32_Server_Gripper");
  DrawDisplay("Connected\n to WiFi");
  connection.loopForever(true);
}; 
TaskHandle_t NetworkTask;




void setup() 
{
  Serial.begin(115200);

  // Initialize the Display
  display.init();
  display.flipScreenVertically();

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);


  xTaskCreatePinnedToCore(networkTask, "networkTask", 4096*2, NULL, 17, &NetworkTask, 0);
}

void loop() {}