# Main Readme for the ROS-Integration of our DIY-Robotarm and Gripper

This Readme file works as an overview about the complete ROS-integration of our robot and gripper. ROS (Robot Operating System) is a open-source software framework for robotics tasks. In the following we will use the ROS2 distribution Humble. 

## Main Ideas/ Tasks
- ROS runs on a LINUX- device and sends control messages to the ESP32 microcontroller on the hardware side. No complex calculations on the ESP32 are needed.
- Ensure that developed ROS-Packages are reusable for other projects -> Modularity is recommendet
- Use docker in development and deployment, so no version and dependencie issues should occur when ROS is running on other computers.
- The 6 axis robotic arm shold be controlled within the ROS2-Control framework, for the gripper only a bool state control (opening and closing) shold be implemented.
- Set up Moveit 2 for motion planning
- Implement the python user interface as known from the other robotic-systems in the IRAS laboratory.

## Structure
As mentioned above modularity is one of our main targets while software-development. Using docker in development and deployment of the packages facilitates to deal with that requirement.
Every ROS robotics project has three key parts.

Part 1 is the description of the robotics hardware. The description package contains all things to represent the hardware inside the ROS-framework such as the URDF-Model.
Our full diy robotics "cell" consists of the 6-axis arm, the gripper and the subframe where the arm is mounted on. So in total wee need 3 seperate packages to describe our diy robot inside the ROS-framework as shown below:

-----GRAFIK DESCRIPTION PACKAGES-------

Part 2 are the drivers. The drivers link the description (digital robot) to the real hardware. For the arm and the gripper we use different control stategies.
Due to the complexity of controlling 6 dependent axis, the arm is fully included in the ROS2-Control framework. The control message to the ESP32 contains the next axis setpoints (next interpolated point in th C-Space when creating trajectories), some status bits and some bits for communication management. Because we kept the hardware as sinple (and cheap) as possible, no sensors for joint-states are included. We operate the arm in an Open-Loop control. If the arm is used inside the specified physical limits, this should not be a disadvantage. For more informations on this point, please switch to the overall-Readme.
Because of simplicity the gripper doesn't need to be integrated in ROS2-Control. The gripper driver package only contains a simple service-definition wich sends a bool (0 or 1) to the robot where 0 equals open and 1 close.
So th total we need 2 seperate driver packages:

------------GRAFIK DREVER PACKAGES------------

Part 3 of our robotics system integration is the application. Firstly these packages contain Moveit configurations to enable motion planning to provide trajectories for the robot. Secondly a user-friendly interface for programming the robot is integrated here. At the end the upcoming users should be able to develop robotic applications with our diy hardware by just writing a simple python code where trajectories and motions (PTP, LIN) could be programmed.

--------GRAFIK APPPLICATION PACKAGES ---------------


## Development
Every mentioned package was developed mor or less independend. 

## Deployment
Startprocedure
