/* This code is made for by Marijn Stijvers, as a student on the department Industrial Design TU/e dec 2018. 
It contains a programm that makes a NEMA Stepper Motor turn by usign the imput of a sonar ultrasonic sensor.
Furthermore it containse a setup program to make the Motor turn one direction until a button is pressed. 
Which is visualized by using light indication. */

  //setup sonar
const int trigPin = 2;
const int echoPin = 4;
const int sensorMin = 0;
const int sensorMax = 35;

  // setup button to go down
const int buttonMotorDown = 5;
int buttonState = 0; // variable for reading the puschbutton status
const int ledPinGreen =  13;      // the number of the green LED pin
const int ledPinRed = 7; // the number of the red LED pin

  // setup motor
const int stepPin = 8; // pin tells steps 
const int dirPin = 9; // pin tells direction to the motor
int delayTime = 10;  // set time of delay between each step, to make speed.
int dupSteps = 10; // dubplicate amount of steps to make cup significantly moving
int stepsTaking; // amount of steps to take by the motor
int OldHight;
int NewHight;


void setup() {
  // basic setup
  Serial.begin(9600);

  //set the two motor pins as output
  pinMode (stepPin, OUTPUT);
  pinMode (dirPin, OUTPUT);

  //Setup button to let the cup go down at the start of each session.
  pinMode(buttonMotorDown, INPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
 

  //TO DO bring the cup down till the bottom is pressed. 
    while (buttonState == LOW){
     digitalWrite(ledPinRed, HIGH);
     buttonState = digitalRead(buttonMotorDown);  //read buttonstate
     for (int l = 0; l <= 200; l++) // 200 is 200 steps is one rotation
      {
      digitalWrite(stepPin, HIGH); // make motor turn one way
      delay(delayTime);
      digitalWrite(stepPin,LOW); // set one step in total
      delay(delayTime);
     }
     Serial.println("setup");
   
    // when button is pressed stop turning. 
    if (buttonState == HIGH){
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinGreen, HIGH);
      digitalWrite(stepPin, LOW); // let motor stop turning 
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
    NewHight =10;
    Serial.println ("NewHight = 1");
    break;
  case 1: // bit further to the sonar
    NewHight =20;
    Serial.println ("NewHight = 2");
    break;  
  case 2: // further to the sonar
    NewHight = 30;
    Serial.println ("NewHight = 3");
    break;
  case 3: // even further to the sonar
    NewHight = 40;
    Serial.println ("NewHight = 4");
    break; 
  case 4: // to far to the sonar
    NewHight = 50;
    Serial.println ("NewHight = 5");
    break;    
  }
  
  // let stepper move, new - old is the amount of steps to take.
  stepsTaking = NewHight - OldHight;
  stepsTaking = stepsTaking*dupSteps;  // make cup significantly moving
  //if stepsTaking is smaller than zero, the cup needs to turn the other direction. 
  if (stepsTaking < 0){
    stepsTaking = stepsTaking*(-1);
    digitalWrite(dirPin, LOW);
    } else { // when stepsTaking >0 the cup needs to go up so direction needs to be High
      digitalWrite(dirPin, HIGH);
      }

  // let motor turn the amount of stepsTaking
  for (int k = 0; k <= stepsTaking ; k++){
     for (int j = 0; j <= 200; j++){ // 200 is 200 steps is one rotation
      digitalWrite(stepPin, HIGH); // make motor turn one way
      delay(delayTime);
      digitalWrite(stepPin,LOW); // set one step in total
      delay(delayTime);
     }
    }
  OldHight = NewHight; //new hight turns into old hight 
  
  
}

long microsecondsToCentimeters(long microseconds)

{return microseconds / 29 / 2;}
