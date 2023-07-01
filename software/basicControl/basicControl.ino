/* Example sketch to control a stepper motor with TB6600 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPinY 2
#define stepPinY 3
#define motorInterfaceTypeY 1
#define limitY 7

#define dirPinX 4
#define stepPinX 5
#define motorInterfaceTypeX 1

// Create a new instance of the AccelStepper class:
AccelStepper stepperY = AccelStepper(motorInterfaceTypeY, stepPinY, dirPinY);

// Create a new instance of the AccelStepper class:
AccelStepper stepperX = AccelStepper(motorInterfaceTypeX, stepPinX, dirPinX);


double yLocation = 100;
int locationSteps = 0;

long initial_homing=-1;  //Initial position that keeps iterating until Stepper hits switch


void setup() {
  Serial.begin(9600);
  pinMode(limitY, INPUT);
 
  // Set the maximum speed and acceleration:
  stepperY.setMaxSpeed(1000);
  stepperY.setAcceleration(1600);
   stepperX.setMaxSpeed(1000);
  stepperX.setAcceleration(1600);


  double locationAngle = atan2 (yLocation, 3000) * 180/3.14159265;
  locationSteps = round(locationAngle*15.555);


  Serial.print("Location Steps:");
  Serial.println(locationSteps);


  delay(2000);


  // Start Homing procedure of Stepper Motor at startup
  Serial.print("Stepper is Homing . . . . . . . . . . . ");


  while (digitalRead(limitY)) {  // Make the Stepper move CCW until the switch is activated  
    stepperY.moveTo(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    stepperY.run();  // Start moving the stepper
    delay(5);
}


  stepperY.setCurrentPosition(0);  // Set the current position as zero for now
  stepperY.moveTo(700);  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperY.setCurrentPosition(0);  // Set the current position as zero for now


  int stepsY = setAngleinStepsY(1020, 2850, 810, 1020);
  int stepsX = setAngleinStepsX(1270,2850, 810, 0);


  stepperY.moveTo(stepsY);  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(stepsX);  // Set the current position as zero for now
  stepperX.runToPosition();


  delay(500);
 

  

  stepperY.moveTo(setAngleinStepsY(1020, 2850, 810, 1020));  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(setAngleinStepsX(1270,2850, 810, 1400));  // Set the current position as zero for now
  stepperX.runToPosition();


    delay(300);




stepperY.moveTo(setAngleinStepsY(1020, 2850, 810, 0));  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(setAngleinStepsX(1270,2850, 810, 1400));  // Set the current position as zero for now
  stepperX.runToPosition();


    delay(300);




stepperY.moveTo(setAngleinStepsY(1020, 2850, 810, 0));  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(setAngleinStepsX(1270,2850, 810, 0));  // Set the current position as zero for now
  stepperX.runToPosition();


    delay(300);




  stepperY.moveTo(setAngleinStepsY(1020, 2850, 810, 1020));  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(setAngleinStepsX(1270,2850, 810, 0));  // Set the current position as zero for now
  stepperX.runToPosition();


}


void loop() {






}








int setAngleinStepsY(double canvasHeight,double gunOffset, double gunHeight, double targetY){


  double locationSteps;
  double locationAngle = atan2 (targetY-gunHeight, gunOffset) * 180/3.14159265;
  locationSteps = -round(locationAngle*15.555);
 
  return locationSteps;
}


int setAngleinStepsX(double canvasWidth,double gunOffset, double gunHeight, double targetX){


 
  double locationSteps;
  double locationAngle = atan2 (targetX, gunOffset) * 180/3.14159265;
  locationSteps = -round(locationAngle*15.555);
 
  return locationSteps;
}
