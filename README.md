# diy_robotics
## Overview
 This repo contains the results of a project work at the University of Applied Sciences Karlsruhe by Robin Wolf, Hannes Bornemann and Mathias Fuhrer.
As part of the project work, the Six-Axis Robot Arm WE-R2.4 from LoboCNC https://www.printables.com/de/model/132260-we-r24-six-axis-robot-arm was set up and a new gripper was developed. The CAD files of the gripper and assembly instructions can be found here: 

Two PCBs were designed for the electrical wiring: one PCB for the 6 axes and one PCB for the gripper. The KiCAD files can be found here:

To control the 6 axes and the gripper, ROS2 implementations were written that communicate via Wifi with an ESP32, from which the axes and the gripper are then moved. One ESP32 is responsible for the 6 axes, the second ESP32 for the gripper.

The ROS2 packages are packaged in Docker containers so that they can be used by others without any problems. The ROS2 packages can be found here:
https://github.com/RobinWolf/diy_robotarm_wer24_driver
https://github.com/RobinWolf/diy_robotarm_wer24_driver
https://github.com/RobinWolf/diy_robot_full_cell_description

https://github.com/RobinWolf/diy_soft_gripper_description
https://github.com/RobinWolf/diy_soft_gripper_driver

The PC on which the ROS2 packages are executed must be connected to the same Wifi as the two ESP32s. The two ESP32s then receive messages from the PC via TCP-IP with the commands for the gripper and the 6-axes and then control the gripper and the axes accordingly. The VS-Code PlatformIO project folders for the ESP32 of the gripper and the axes can be found here:




## Possible improvements
- Conversion of the robot to metric screws
- Endstops or sensors to determine the position of the robot or to move it to a home position 


