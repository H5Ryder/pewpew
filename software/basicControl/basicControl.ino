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

long initial_homing = -1;  //Initial position that keeps iterating until Stepper hits switch


void setup() {
  Serial.begin(9600);
  pinMode(limitY, INPUT);

  // Set the maximum speed and acceleration:
  stepperY.setMaxSpeed(1000);
  stepperY.setAcceleration(1600);
  stepperX.setMaxSpeed(1000);
  stepperX.setAcceleration(1600);


  double locationAngle = atan2(yLocation, 3000) * 180 / 3.14159265;
  locationSteps = round(locationAngle * 15.555);


  Serial.print("Location Steps:");
  Serial.println(locationSteps);


  delay(2000);


  // Start Homing procedure of Stepper Motor at startup
  Serial.print("Stepper is Homing . . . . . . . . . . . ");


  while (digitalRead(limitY)) {       // Make the Stepper move CCW until the switch is activated
    stepperY.moveTo(initial_homing);  // Set the position to move to
    initial_homing--;                 // Decrease by 1 for next move if needed
    stepperY.run();                   // Start moving the stepper
    delay(5);
  }


  stepperY.setCurrentPosition(0);  // Set the current position as zero for now
  stepperY.moveTo(700);            // Set the current position as zero for now
  stepperY.runToPosition();
  stepperY.setCurrentPosition(0);  // Set the current position as zero for now


  int stepsY = setAngleinStepsY(1020, 2850, 810, 1020);
  int stepsX = setAngleinStepsX(1270, 2850, 810, 0);


  stepperY.moveTo(stepsY);  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(stepsX);  // Set the current position as zero for now
  stepperX.runToPosition();


  delay(500);




  stepperY.moveTo(setAngleinStepsY(1020, 2850, 810, 1020));  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(setAngleinStepsX(1270, 2850, 810, 1400));  // Set the current position as zero for now
  stepperX.runToPosition();


  delay(300);




  stepperY.moveTo(setAngleinStepsY(1020, 2850, 810, 0));  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperX.moveTo(setAngleinStepsX(1270, 2850, 810, 1400));  // Set the current position as zero for now
  stepperX.runToPosition();
}


void loop() {
}








int setAngleinStepsY(double canvasHeight, double gunOffset, double gunHeight, double targetY) {


  double locationSteps;
  double locationAngle = atan2(targetY - gunHeight, gunOffset) * 180 / 3.14159265;
  locationSteps = -round(locationAngle * 15.555);

  return locationSteps;
}


int setAngleinStepsX(double canvasWidth, double gunOffset, double gunHeight, double targetX) {



  double locationSteps;
  double locationAngle = atan2(targetX, gunOffset) * 180 / 3.14159265;
  locationSteps = -round(locationAngle * 15.555);

  return locationSteps;
}

void printArt() {

  
  int yCoord[354] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,32,32,32,32,32,31,30,29,28,27,26,25,24,23,22,21,20,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,4,4,4,24,25,26,27,28,28,27,26,25,24,32,32,32,32,32,32,32,32,32,31,30,29,29,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,29,29,29,28,27,26,25,24,23,22,21,20,20,20,20,20,19,18,17,17,17,17,17,16,15,14,13,12,11,10,9,8,7,7,7,7,7,6,5,4,4,4,4,4,4,4,4,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,4,4,4,4,5,6,6,7,8,9,8,7,6,6,5,4,6,6,5,6,5,4,4,4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,32,32,32,32,32,31,30,29,28,27,26,25,23,24,22,21,20,19,18,17,16,15,14,13,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,32,32,32,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,12,12,12,12,12,12,12,12,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,32,32,32,32,8,9,10,11,8,9,10,11};
  int xCoord[354] = {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,8,9,10,11,12,13,14,15,15,15,15,15,14,13,12,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,8,7,9,9,9,9,9,10,11,12,11,10,19,20,21,22,23,24,25,26,27,27,27,27,26,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,25,24,23,23,23,23,23,23,23,23,23,23,24,25,26,27,27,27,27,26,25,24,23,23,23,23,23,23,23,23,23,23,23,24,25,26,27,27,27,27,26,25,24,23,22,21,20,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,32,33,34,35,36,36,36,36,37,38,39,40,40,41,40,41,42,43,44,45,46,47,47,47,45,39,39,48,48,48,49,50,51,51,51,51,52,53,54,55,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,43,44,42,41,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,32,33,34,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,36,37,38,39,40,46,47,48,49,50,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,52,53,54,55,53,54,55,56,36,35,34,33};

  


}
