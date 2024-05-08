#ifndef AXIS_HPP
#define AXIS_HPP

#include <vector>
#include <string>
#include <AccelStepper.h> 
#include "Configuration.h"


class Axis {
//*******************************************************************************************************************
//***********************define private class variables and methods (only callable inside the class******************
//*******************************************************************************************************************
private:
  AccelStepper _stepper;            // Stepper Object initialized from Accelstepper adapted for SR
	bool _invertDirection = false;    // If TRUE, the axis is inverted
	double _gearing = -1;             //gearing given in config-file for all axis 1/38.4
  double _microsteps = -1;          //still to implement!
  double _stepsPerRev = -1;         //still to implement
  int _axisNumber = -1;             // Axis Number Identifier (1...6) -> default -1 to detect improperly initialized objects         
  int _minPos;
  int _maxPos;

  // Output Pin Information
  struct {
    bool invertOutputEnable = false;      // If True, HIGH to Disable the stepper -> default: HIGH to enable Steppers
    int step, direction;
  } _outputs; 

  // Position information
  struct Position {
    double setpoint = 0;
    double current = 0;
  } _position;

	
  // Get the distance between the current position and the setpoint
	double _distance() {
		if (_position.setpoint > _position.current) return (_position.setpoint - _position.current);
		else return (_position.current - _position.setpoint);
	};


//*****************************************************************************************
//*******************public Methods, callable in the main**********************************
//*****************************************************************************************
public:
  // Axis Constructor for DRV8825 Drivers
  Axis(int number, uint8_t stepPin, uint8_t directionPin, double gearing, int stepsPerRev, int microsteps, int minPos, int maxPos, int velMax, int accMax, bool invertDirection = false) 
  {
    _axisNumber = number;
    _invertDirection = invertDirection;
		_gearing = gearing;
    _microsteps = microsteps;
    _stepsPerRev = stepsPerRev;

    //Define a stepper with the DRV8825 Driver
    _stepper = AccelStepper(AccelStepper::DRIVER, stepPin, directionPin);

    // Set min and max axis positions
    _minPos = minPos;
    _maxPos = maxPos;

    // Set maximum acceleration
    _stepper.setAcceleration(accMax);

    // Set maximum speed
    _stepper.setMaxSpeed(velMax);

		Axis::axisList.push_back(this); // Add the axis to the global list
    //see at the bottom of the class: push_back(this) adds pointer (this) to the current Axis object to the class
    //this allows iterating over all objects, e.g. for run()
	}


  // Get the current position in Degrees --> for feedback (not from motor, but axis position)
  double getPosition() {
    int invertParam = 1;
    if(_invertDirection) invertParam = -1;    // Adjust rotation direction
    return (double) (_stepper.currentPosition()/(_stepsPerRev * _microsteps * _gearing) * 360.0 * invertParam);   // Conversion from Steps to Degrees
  }



  // Move the axis relative to the current position (degrees)
	// void moveToRelativePosition(double position) { moveToPosition(getPosition() + position); };

  // Move the axis to an absolute position (degrees)
	void moveToPosition(double position)  
  {
    if (position > _maxPos) 
    {
      position = _maxPos;
      // Serial.println("position > _maxPos");
    }

    else if (position < _minPos) 
    {
      position = _minPos;
      // Serial.println("position < _minPos");
    }
    
    long stepSetpoint = 0;
    //Conversion from Degrees to Steps for the Accelstepper class
    int invertParam = 1;
    if(_invertDirection) invertParam = -1;    // Adjust rotation direction

    stepSetpoint = position/360.0 * _stepsPerRev * _microsteps * _gearing * invertParam;  // Conversion from Degrees to Steps
    _stepper.moveTo(stepSetpoint);
	};
 
  // Polling function controlling the motor:
	void runMotor() { _stepper.run(); }   // only this axis

  // Static function to poll all the existing motors:
	static void runAll() { //1 poll -> execute 1 step
    for (Axis * axis : Axis::axisList) axis->runMotor();  // all axes in axisList
	};

  // Static list of pointers to all axis instances. This allows iterating over all of them
	static std::vector<Axis *> axisList;  //see above
};

std::vector<Axis *> Axis::axisList; // Instantiate the static axis list
//std::vector<> is like an array that contains the pointer addresses of all Axis objects
// Axis:: means that the definition for the variable axisList is static,
// so it is the same for all instances of the Axis class and can be accessed in all instances

#endif