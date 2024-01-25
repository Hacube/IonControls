// myServo.h
#include "arduino.h"

class myServo
{
  public:
  myServo(int servoPin, float mSecPerDegree, int zeroPulseWidth); // This is the constructor and can have inputs
  
  void write(float degrees); // function
  
  private:
  int _servoPin;
  float _mSecPerDegree;
  int _zeroPulseWidth;
};