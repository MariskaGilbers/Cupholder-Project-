#include <Stepper.h>


/* 
 *  stepsPerRevolution geeft aan hoeveel stapjes de microcontroller moet doen om 1
 *  keer rond te draaien.
 */
const int stepsPerRevolution = 360;
const int trigPin = 2;
const int echoPin = 4;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

/*
 * 
 * Variabele om de aantal stapjes in op te slaan.
 * Per rotatie is dat dus 360 stapjes.
 * Long variabele is 4 bytes breed en kan dus een hele hoop stapjes opslaan.
 * 
 */
long aantalstapjes = 0;

/*
 * 
 * variabele om het aantal rotaties te berekenen
 * Ook weer een long.
 * 
 */
long aantalrotaties = 0;

void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(50);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
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

Serial.print(cm);

Serial.print("cm");

Serial.println();

delay(500);





  if (cm  < 10) {
    
    Serial.print("downwards");

    // aan myStepper.step(x) kun je een variabele mee geven.
    // in dit geval doe je altijd 360 stapjes.
    // probeer eens het getal 180 of stepsPerRevolution / 2 in te vullen
    // en kijk wat er gebeurd.
    myStepper.step(stepsPerRevolution);

    // variabele updaten met het aantal stapjes
    //aantalstapjes = aantalstapjes + stepsPerRevolution; 
    // variabele updaten met het aantal rotaties
   // aantalrotaties = aantalstapjes / stepsPerRevolution;

    // het aantal stapjes naar de pc sturen
    //Serial.println(aantalstapjes);
    //Serial.print(" Aantal rotaties: ");

    // het aantal rotaties naar de pc sturen
    //Serial.println(aantalrotaties);
  }
  
  if (cm >= 10 && cm <=20) {
    
    Serial.println("upwards");
    myStepper.step(-stepsPerRevolution);
    
    //aantalstapjes = aantalstapjes - stepsPerRevolution;
    //aantalrotaties = aantalstapjes / stepsPerRevolution;
    
    //Serial.print(aantalstapjes);
    //Serial.print(" Aantal rotaties: ");
    //Serial.println(aantalrotaties);
  }

  if (cm > 20){
  Serial.println("Stop");
  myStepper.step(0);
  }
}
long microsecondsToCentimeters(long microseconds)

{return microseconds / 29 / 2;}

