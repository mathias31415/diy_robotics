#include <AccelStepper.h>
#include <MultiStepper.h>


const int stepPin = 9;
const int directionPin = 7;
char task;2
const float st = 7.5; // 7.5 = Minibea // 1.8 = NEMA
//const float st = 1.8; // 7.5 = Minibea // 1.8 = NEMA
const int ms =50;

AccelStepper TestMotor(AccelStepper::DRIVER, stepPin, directionPin);

void setup() {
  Serial.begin(115200);

  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);

  TestMotor.setMaxSpeed(500 * ms/st);  //Steps/s
  TestMotor.setAcceleration(250*ms/st); //Steps/s²

}

void loop() {
  TestMotor.run();
  //Serial.println(TestMotor.distanceToGo());


while (Serial.available() > 0){
    task = Serial.read();

      if(task == 'r'){
        TestMotor.move(-360*ms/st);
        Serial.println("CCW movement");
      }
      else if(task == 'f'){
        TestMotor.move(360*ms/st); //200 = 1 Stepperumdrehung
        Serial.println("CW movement");
      }

   }

 }
