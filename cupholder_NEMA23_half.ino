/* stepper motor control code for DRV8825

*/

// define pins used:

// setup motor
//const int stepPin = 8; // pin tells steps
//const int dirPin = 9; // pin tells direction to the motor
#define stepPin 8 //pin tells steps to take by the motor
#define dirPin 9 // pin tells direction to the motor

int delayTime = 500;  // set time of delay between each step, to make speed.
int dupSteps = 10; // dubplicate amount of steps to make cup significantly moving
int stepsTaking; // amount of steps to take by the motor
int OldHight;
int NewHight;
int SetDirection;

//setup sonar
//const int trigPin = 11;
//const int echoPin = 10;
#define trigPin 11 // sonar input
#define echoPin 10 // sonar output

const int sensorMin = 0;
const int sensorMax = 25;

//setup button
//const int buttonMotorDown = 2;
#define buttonMotorDown 2 // motor moving down button
int buttonState = 0; // variable for reading the puschbutton status
int done = 0; //state for setup 

//const int ledPinGreen =  13;      // the number of the green LED pin
//const int ledPinRed = 7; // the number of the red LED pin
#define ledPinGreen 13 // the number of the green LED 
#define ledPinRed 6 // the number of the red LED pin

long microsecondsToCentimeters(long microseconds)

{
  return microseconds / 29 / 2;
}

void setup()
{ Serial.begin(9600);

  // set the two pins as outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}


void loop()
{
  //TO DO bring the cup down till the bottom is pressed.
  while (done == 0) {
    digitalWrite(ledPinRed, HIGH);
    buttonState = digitalRead(buttonMotorDown);
    Serial.print("buttonState : ");
    Serial.println(buttonState); //read buttonstate
    if (buttonState == LOW) {
      digitalWrite(dirPin, HIGH); //move down
      for (int l = 0; l <= 200; l++) // 200 is 200 steps is one rotation
      {
        digitalWrite(stepPin, HIGH); // make motor turn 
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW); // set one step in total
        delayMicroseconds(500);
      }
      delay(1000);
      Serial.println("setup");
    }
    // when button is pressed stop turning.
    if (buttonState == HIGH) {
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinGreen, HIGH);
      Serial.println("startProgram");
      done = 1;
      OldHight = 1;
    }
  }

  // pinModes and setup sonar
  long duration, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  int range = map(cm, sensorMin, sensorMax, 0, 4); //set ranges for the sonar

  Serial.print("Range : ");
  Serial.println(range);


  //delay(1000); //why is this delay here?

  // set the values of the new hight.
  switch (range) {
    case 0: // close to the sonar
      NewHight = 1;
      Serial.println ("NewHight = 1");
      break;
    case 1: // bit further to the sonar
      NewHight = 2;
      Serial.println ("NewHight = 2");
      break;
    case 2: // further to the sonar
      NewHight = 3;
      Serial.println ("NewHight = 3");
      break;
    case 3: // even further to the sonar
      NewHight = 4;
      Serial.println ("NewHight = 4");
      break;
    case 4: // to far to the sonar
      NewHight = 5;
      Serial.println ("NewHight = 5");
      break;
  }

  // print in serial monitor for verification.
  Serial.print("OH ; ");
  Serial.println(OldHight);
  Serial.print("NH : ");
  Serial.println(NewHight);
  Serial.print("cm ; ");
  Serial.println(cm);


  // let stepper move, new - old is the amount of steps to take.
  stepsTaking = (NewHight - OldHight) * dupSteps; // make cup significantly moving
  Serial.print("stepsTaking: ");
  Serial.println(stepsTaking);

  if (OldHight != NewHight) {
    //if stepsTaking is smaller than zero, the cup needs to turn the other direction.
    //move up
    if (stepsTaking > 0) {
      SetDirection = LOW;
      delay(100);


    } else  { // when stepsTaking < 0 the cup needs to go up so direction needs to be High
      //move down
      SetDirection = HIGH;
      delay(100);
      stepsTaking = abs(stepsTaking);
    }

    // let motor turn the amount of stepsTaking
    for (int k = 0; k < stepsTaking ; k++) {
      //digitalWrite(dirPin, SetDirection);

      Serial.print("direction: ");
      Serial.println(SetDirection);

      for (int j = 0; j < 200; j++) { // 200 is 200 steps is one rotation
        digitalWrite(dirPin, SetDirection);
        digitalWrite(stepPin, HIGH); // make motor turn one way
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW); // set one step in total
        delayMicroseconds(500);
      }

      Serial.println("TURN end"); // feedback

      delay(100); // delay for one second
    }
  }
  OldHight = NewHight; //new hight turns into old hight
  Serial.println("End loop iteration");
  Serial.println("------------------------------");
  delay(500);
}








//digitalWrite(dirPin,HIGH); //Enables the motor to move in a perticular direction
//// for one full rotation required 200 pulses
//for(int x = 0; x < 200; x++){
//  digitalWrite(stepPin,HIGH);
//  delayMicroseconds(500);
//  digitalWrite(stepPin,LOW);
//  delayMicroseconds(500);
//}
//delay(1000); // delay for one second
//
//
//digitalWrite(dirPin,HIGH); //Enables the motor to move in a opposite direction
//// for three full rotation required 600 pulses
//for(int x = 0; x < 600; x++){
//  digitalWrite(stepPin,HIGH);
//  delayMicroseconds(500);
//  digitalWrite(stepPin,LOW);
//  delayMicroseconds(500);
//}


