# Drive Concept
## Power limitation

After the gripper got assembled the first time, the powering servo motors quickly overheated and stopped functioning during the first tests. Because the servo can not reach the programmed closing position due to the object blocking further move-ment of the gripper jaws, the servo motor switches to stall operation mode. This cau-ses the servo motor to stall, putting it under maximum stress and leads to its breakdown.
To counteract this, it was decided to use "continuous drive" servos. These servo types do not move to a set angle like the standard models. Instead, the length of the "HIGH" level control signal is set in the code by a value in microseconds. This is then mapped to an equivalent power level of the motor, making it possible to operate the motor at a fraction of its maximum power to prevent it from overloading and crashing. As these servos do not differ externally from the standard version, the drive can be replaced without having to adapt the assembly.

## Testing

When testing the gripper with limited power, the servo withstood approx. 30 % of the maxiumum power for a longer period of time, before breaking down with a higher setting. This setting enables the gripper to close with a force of 6.5 N, which is enough to lift small objects. However, the pinion mounted on the servo's electric mo-tor slipped off the drive shaft several times, which was a major cause of failure, apart from overheating. In hope to get a more realiable solution, there were some more servos of different manufacturers ordered to test them. Therefor they got mounted into a test bar with stop collars to simulate the gripper getting blocked by an object.This simplification oft the servos load when driving the gripper allows to test all servos simultaneously and to wear down only one servo of each kind. 

PICTURE TEST BAR

Servo 0 is the one ordered at the beginning, on which the pinion has come loose. It has plastic gears. Servo 3 is another servo with plastic gearing from a different ma-nufacturer and servos 1 and 2 are servos from different manufacturers with metal gearing.
The closing time is set to 10 s and the opening time is 1 s, whereby the load on the motors is increased by 10% after each test run.  A test run is evaluated as passed after 500 cycles (approx. 1.5 h).

## Result

Servo 1 fails after about 100 cycles at 30% power. Servo 0 and Servo 3 fail in the following run at 40% power after about 65 and 140 cycles respectively. Finally, servo 2 fails after about 70 cycles at 50% power. As the servos have different maximum torques, the closing force that the gripper can apply with the respective servomotors installed is now measured when the servomotors are operated within the permissible range (10% below failure).
Result:

Servo 0: 6.57 N

Servo 1: 5.18 N

Servo 2: 6.44 N

Servo 3: 5.36 N

Servo 0 offers the best performance with a closing force of 6.57 N. However, due to the loosening gear, the reliability of this servo is rated as insufficient, so the servo with the next lowest closing force is selected. Servo 2 has a closing force of 6.44 N, just below that of servo 0. It also has a metal gear, which should give it a longer life
