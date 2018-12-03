#include <Stepper.h>


/* 
 *  stepsPerRevolution geeft aan hoeveel stapjes de microcontroller moet doen om 1
 *  keer rond te draaien.
 */
const int stepsPerRevolution = 180;
const int trigPin = 2;
const int echoPin = 4;
int OldHight;
int NewHight;
const int sensorMin = 0;
const int sensorMax = 35;


  // setup button to go down
const int buttonMotorDown = 5;
int buttonState = 0; // variable for reading the puschbutton status
const int ledPinGreen =  13;      // the number of the green LED pin
const int ledPinRed = 7; // the number of the red LED pin

  // setup motor
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // basic setup
  myStepper.setSpeed(50);
  Serial.begin(9600);

  //Setup button to let the cup go down at the start of each session.
  pinMode(buttonMotorDown, INPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
 

  //TO DO bring the cup down till the bottom is pressed. 
    while (buttonState == LOW){
    buttonState = digitalRead(buttonMotorDown);  //read buttonstate
    myStepper.step(stepsPerRevolution);
    Serial.println("setup");
    digitalWrite(ledPinRed, HIGH);
    
    if (buttonState == HIGH){
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinGreen, HIGH);
      Serial.println("startProgram"); 
      break; 
      }
     }  


  OldHight == 1;

}
  
void loop() {
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
 
  // print in serial monitor for verification. 
Serial.println("new!!!!!!!!!");
Serial.println("OH");
Serial.println(OldHight);
Serial.println("cm");
Serial.println(cm);

delay(1000); //why is this delay here?

// set the values of the new hight. 
switch (range){
  case 0: // close to the sonar
    NewHight =1;
    Serial.println ("NewHight = 1");
    break;
  case 1: // bit further to the sonar
    NewHight =2;
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
  
 // let stepper move, new- old is the amount of steps to take.
  myStepper.step(stepsPerRevolution*(NewHight-OldHight));
  OldHight = NewHight; //new hight turns into old hight 
  
  
}

long microsecondsToCentimeters(long microseconds)

{return microseconds / 29 / 2;}
