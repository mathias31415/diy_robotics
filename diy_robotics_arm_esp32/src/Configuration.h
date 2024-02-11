#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

struct AxisLimits {
  float speed, acceleration;
  double maxPosition, minPosition;
};
struct Settings {
  AxisLimits axisLimits[7];   // Only using indices 1...6
  bool initialized = false;
} settings;

#define NETWORK_SSID "DIY-Robotics"
#define NETWORK_PASSWORD "87654321"
#define IP_ADDRESS 192, 168, 212, 203 // Gripper 202, Arm 203
#define GATEWAY_IP 10, 42, 0, 1
#define SUBNET_MASK 255, 255, 255, 0

// Axis 1 uses a DRV8825 Driver, NEMA 17
#define STEPPER_1_STEP 16
#define STEPPER_1_DIR 13
#define AXIS_1_GEARING 38.4   // i = n_Input/n_Output = 38.4/1 = 38.4
#define AXIS_1_STEPS_PER_REV 200
#define AXIS_1_MICROSTEPS 8   // M0 = 1, M1 = 1, M2 = 0  --> 1/8 microstepping
#define AXIS_1_POS_MIN -135
#define AXIS_1_POS_MAX 135
#define AXIS_1_VEL_MAX 1000
#define AXIS_1_ACC_MAX 1000
#define AXIS_1_INVERT_DIRECTION false     // to match axis rotation direction with simulation rotation direction

// Axis 2 uses a DRV8825 Driver, NEMA 17
#define STEPPER_2_STEP 18
#define STEPPER_2_DIR 17
#define AXIS_2_GEARING 38.4
#define AXIS_2_STEPS_PER_REV 200
#define AXIS_2_MICROSTEPS 8 
#define AXIS_2_POS_MIN -120
#define AXIS_2_POS_MAX 120
#define AXIS_2_VEL_MAX 1000    
#define AXIS_2_ACC_MAX 1000
#define AXIS_2_INVERT_DIRECTION false

// Axis 3 uses a DRV8825 Driver, NEMA 17
#define STEPPER_3_STEP 5
#define STEPPER_3_DIR 19
#define AXIS_3_GEARING 38.4
#define AXIS_3_STEPS_PER_REV 200
#define AXIS_3_MICROSTEPS 8 
#define AXIS_3_POS_MIN -150
#define AXIS_3_POS_MAX 150
#define AXIS_3_VEL_MAX 1000
#define AXIS_3_ACC_MAX 1000
#define AXIS_3_INVERT_DIRECTION true

// Axis 4 uses a DRV8825 Driver, MINIBEA
#define STEPPER_4_STEP 25
#define STEPPER_4_DIR 23
#define AXIS_4_GEARING 38.4
#define AXIS_4_STEPS_PER_REV 48
#define AXIS_4_MICROSTEPS 8 
#define AXIS_4_POS_MIN -120
#define AXIS_4_POS_MAX 120
#define AXIS_4_VEL_MAX 400     
#define AXIS_4_ACC_MAX 800
#define AXIS_4_INVERT_DIRECTION true

// Axis 5 uses a DRV8825 Driver, MINIBEA
#define STEPPER_5_STEP 27
#define STEPPER_5_DIR 26
#define AXIS_5_GEARING 38.4
#define AXIS_5_STEPS_PER_REV 48
#define AXIS_5_MICROSTEPS 8 
#define AXIS_5_POS_MIN -120
#define AXIS_5_POS_MAX 120
#define AXIS_5_VEL_MAX 400     
#define AXIS_5_ACC_MAX 800
#define AXIS_5_INVERT_DIRECTION true

// Axis 6 uses a DRV8825 Driver, MINIBEA
#define STEPPER_6_STEP 33
#define STEPPER_6_DIR 32
#define AXIS_6_GEARING 38.4
#define AXIS_6_STEPS_PER_REV 48
#define AXIS_6_MICROSTEPS 8 
#define AXIS_6_POS_MIN -175
#define AXIS_6_POS_MAX 175
#define AXIS_6_VEL_MAX 400     
#define AXIS_6_ACC_MAX 800
#define AXIS_6_INVERT_DIRECTION true

// define enable pin for all Axis (connected on Hardware)
#define ENABLE_ALL 4

// check if hardware enable switch is enabled (HIGH when ENABLE_ALL is HIGH and Switch is ON)
#define HARDWARE_ENABLE 34  

#endif
