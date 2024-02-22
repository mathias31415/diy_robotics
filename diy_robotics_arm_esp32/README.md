# diy_robotics_arm_esp32
This code initializes a robotic system with multiple axes, each controlled by a stepper motor. It uses an ESP32 microcontroller, a display (SSD1306), and communicates with a PC over WiFi. The code defines the axes, sets up communication, and handles data reception from the PC. The robotic system is activated or deactivated based on commands from the PC. The code continuously checks for updates from the PC, adjusts axis positions accordingly, and updates the display with relevant information. Additionally, it handles the network connection and performs tasks on a separate task core. The main loop continuously runs the axes' control logic.


Bitte noch hinzufügen, weil darauf in arm_driver package verwiesen:
- Message Format
- RobotConnection class methosd

