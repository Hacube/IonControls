// myServo.cpp
#include "arduino.h"
#include "myServo.h"

myServo::myServo(int servoPin, float mSecPerDegree, int zeroPulseWidth)
{
  // Define variables here
  // Set anything the class must do initially here
  _servoPin = servoPin;
  _zeroPulseWidth = zeroPulseWidth;
  _mSecPerDegree = mSecPerDegree;
  pinMode(_servoPin, OUTPUT);
}

void myServo::write(float degrees)
{
  float pulse = _zeroPulseWidth+_mSecPerDegree*1000*degrees;

  digitalWrite(_servoPin, HIGH);  //Write a HIGH value to the digital pin
  delayMicroseconds(pulse);       //Wait the desired pulse time
  digitalWrite(_servoPin, LOW);   //Write a LOW value to the digital pin
  delayMicroseconds(20000-pulse); //Wait 20 milliseconds
}