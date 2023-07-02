  //FACTS: 950 STEPS TO PULL TRIGGER



#include <AccelStepper.h>

#define dirPinT 8
#define stepPinT 9
#define motorInterfaceTypeT 1


#define limitY 7


// Create a new instance of the AccelStepper class:
//AccelStepper stepperT = AccelStepper(motorInterfaceTypeT, stepPinT, dirPinT);

AccelStepper stepperT = AccelStepper(1, 9, 8);




void setup() {

//Set limit switch
  pinMode(limitY, INPUT);


  // Set the maximum speed and acceleration:
  stepperT.setMaxSpeed(250);
  stepperT.setAcceleration(600);


//Find starting position
  while (digitalRead(limitY)) {      // Make the Stepper move CCW until the switch is activated
    stepperT.setCurrentPosition(0);  // Decrease by 1 for next move if needed
    stepperT.moveTo(30);       // Set the position to move to
    stepperT.runToPosition();  // Start moving the stepper
  }


stepperT.moveTo(-700);
stepperT.runToPosition();
delay(10);
stepperT.moveTo(0);
stepperT.runToPosition();
            
}

void loop() {

  stepperT.moveTo(-850);
stepperT.runToPosition();
delay(10);
stepperT.moveTo(0);
stepperT.runToPosition();
delay(10);






  // put your main code here, to run repeatedly:
}
