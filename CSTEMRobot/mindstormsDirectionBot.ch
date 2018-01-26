/* File: mindstormsDirectionBot.ch
   Move a Mindstorms forward or backward using a push button. */
#include <wiringPi.h>
#include <mindstorms.h>
CMindstorms robot;
double radius = 1.1;    // Radius in inches
double speed = 5.0;     // Speed in inches/second
int switchVal;
int directionPin = 18;
int ledPin = 4;

wiringPiSetupGpio(); 
pinMode(directionPin, INPUT);
pinMode(ledPin, OUTPUT);

// Drives the robot continuously
robot.driveForeverNB();

while(1){
    //Reads the button value
    switchVal = digitalRead(directionPin);
    delay(50);
    // Reverses direction
    if(switchVal == HIGH){
        speed = -speed; 
        robot.setSpeed(speed,radius);
        robot.driveForeverNB();
    }
    // Turns on LED if going forward, off if backward
    if (speed >= 0){
        digitalWrite(ledPin, HIGH);
    }
    else {
        digitalWrite(ledPin, LOW);
    }
}
