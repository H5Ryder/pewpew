//BIG LIST OF CONSTANTS
#define yHomeSteps 700 //STEPS TO TAKE Y FROM MICROSWITCH (ACTIVATED) POSITION TO 0 (So that the gun is horizontal)

#define canvasHeight 2000
#define canvasWidth 500
#define gunOffset 1660
#define stepsPerRev 800 //X and Y Stepper Steps
#define stepsPerRevTrigger 400 //Trigger Stepper Steps
#define gearRatio 8 //Ratio between pulleys
#define degreeToSteps 17.78 //For every one degree angle change, the stepper moves 17.78 steps

//-----------------------------------------------------------
#include <AccelStepper.h>

#define dirPinY 2
#define stepPinY 3
#define motorInterfaceTypeY 1
#define limitY 7

#define dirPinX 4
#define stepPinX 5
#define motorInterfaceTypeX 1

#define dirPinT 8
#define stepPinT 9
#define motorInterfaceTypeT 1


AccelStepper stepperT = AccelStepper(motorInterfaceTypeT, stepPinT, dirPinT);
AccelStepper stepperY = AccelStepper(motorInterfaceTypeY, stepPinY, dirPinY);
AccelStepper stepperX = AccelStepper(motorInterfaceTypeX, stepPinX, dirPinX);





void setup() {
  pinMode(limitY, INPUT);  //Set limit switch

  stepperY.setMaxSpeed(1000);
  stepperY.setAcceleration(1600);
  stepperX.setMaxSpeed(1000);
  stepperX.setAcceleration(1600);
  stepperT.setMaxSpeed(600);
  stepperT.setAcceleration(600);

  while (digitalRead(limitY)){

  }

  homeY();
  //homeX(-10);
  //homeTrigger();
  //testTrigger();
  delay(1000);
  aimAndFire(10, 100, true);

}

void loop() {
  // put your main code here, to run repeatedly:
}



void homeY() {

  stepperY.setCurrentPosition(0);
  stepperY.moveTo(-900);
  stepperY.runToPosition();

  while (digitalRead(limitY)) {  // Make the Stepper move CCW until the switch is activated
    stepperY.moveTo(-10);        // Set the position to move to
    stepperY.run();       // Start moving the stepper
    stepperY.setCurrentPosition(0);
    delay(1);
  }

  stepperY.moveTo(yHomeSteps);  // Set the current position as zero for now
  stepperY.runToPosition();
  stepperY.setCurrentPosition(0);  // Set the current position as zero for now
}

void homeTrigger() {
  stepperT.setCurrentPosition(0);  // Decrease by 1 for next move if needed

  while (digitalRead(limitY)) {      // Make the Stepper move CCW until the switch is activated
    stepperT.moveTo(30);             // Set the position to move to
    stepperT.runToPosition();        // Start moving the stepper
    stepperT.setCurrentPosition(0);  // Decrease by 1 for next move if needed
  }
}


void testTrigger(){

  for (int i = 0; i <= 40; i++) {
  stepperT.moveTo(-700);
  stepperT.runToPosition();
  delay(10);
  stepperT.moveTo(0);
  stepperT.runToPosition();
  }
}

void homeX(int val){

  stepperX.setCurrentPosition(0);

   while (digitalRead(limitY)) {  // Make the Stepper move CCW until the switch is activated
    stepperX.moveTo(val);        // Set the position to move to
    stepperX.runToPosition();    // Start moving the stepper
    stepperX.setCurrentPosition(0);
  }

}

void aimAndFire(int x, int y, bool fire) {
  rotateY(calculateYAngleSteps(y));
  rotateX(calculateXAngleSteps(x));

  if (fire) {pullTrigger();}


}

int calculateYAngleSteps(int y){

  float angle = atan2(y, gunOffset) * 180 / 3.14159265; //degrees
  return -round(angle * degreeToSteps); //returns how many steps the stpper motor needs to take to achieve desired angle


}

int calculateXAngleSteps(int x){

  float halfW = canvasWidth/2;

  float angle = atan2(halfW - x, gunOffset) * 180 / 3.14159265; //degrees
  return round(angle * degreeToSteps); //returns how many steps the stpper motor needs to take to achieve desired angle


}

void rotateY(int steps) {
   stepperY.moveTo(steps);        // Set the position to move to
   stepperY.runToPosition(); 
}

void rotateX(int steps) {
   stepperX.moveTo(steps);        // Set the position to move to
   stepperX.runToPosition(); 
}

void pullTrigger() {
  stepperT.moveTo(-700);
  stepperT.runToPosition();
  stepperT.moveTo(0);
  stepperT.runToPosition();

}
