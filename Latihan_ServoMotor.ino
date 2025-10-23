/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/


#include <Servo.h>

Servo motorServo;

#define pinMotorServo 3

#define pinButton 2

void setup() {
  Serial.begin(9600);
  Serial.println("Program Motor Servo");
  motorServo.attach(pinMotorServo);
  motorServo.write(0);

  pinMode(pinButton, INPUT_PULLUP);
  // put your setup code here, to run once:

}

void loop() {
  // Serial.println("Putar 180 Derajat");
  // motorServo.write(180);

  // delay(2000);
  //  Serial.println("Putar 0 Derajat");
  //  motorServo.write(0);

   if(digitalRead(pinButton)==LOW){
    Serial.println("Servo 180 Derajat");
    motorServo.write(189);

   }else {
    Serial.println("Servo 0 Derajat");
    motorServo.write(0);
   }
   delay(200);
  // put your main code here, to run repeatedly:

}

