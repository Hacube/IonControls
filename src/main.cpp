#include <myServo.h>
#include <Arduino.h>
#include <Wire.h> // library allows communication with I2C / TWI devices
#include <math.h> // library includes mathematical functions

// Servo pins
int servoOnePin = 3;
int servoTwoPin = 5;

float mSecPerDegree = 0.011; // milliseconds per degree of rotation
int zeroPulseWidth = 1500;   // microseconds at 1 millisecond pulsewidth, servo motor goes to 0 position

const int MPU = 0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ; // 16-bit integers
double zeroPitch,zeroRoll,pitch,roll;

myServo leftServo(servoOnePin, mSecPerDegree, zeroPulseWidth);
myServo rightServo(servoTwoPin, mSecPerDegree, zeroPulseWidth);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  digitalWrite(buzzPin, LOW);

  Wire.begin();                // initiate wire library and I2C
  Wire.beginTransmission(MPU); // begin transmission to I2C slave device
  Wire.write(0x6B);            // PWR_MGMT_1 register
  Wire.write(0);               // set to zero (wakes up the MPU-6050)  
  Wire.endTransmission(true);  // ends transmission to I2C slave device
  Serial.begin(9600);          // serial communication at 9600 bauds

  leftServo.write(0);   // sets the left servo position
  rightServo.write(0);  // sets the right servo position

  callibrate();
}

void loop() {
  Wire.beginTransmission(MPU);  // begin transmission to I2C slave device
  Wire.write(0x3B);             // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);  // restarts transmission to I2C slave device
  Wire.requestFrom(MPU,6,true); // request 14(6?) registers in total  

  //read accelerometer data
  AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) 0x3C (ACCEL_XOUT_L)  
  AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) 0x3E (ACCEL_YOUT_L) 
  AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) 0x40 (ACCEL_ZOUT_L)

  //get pitch/roll
  getAngle(AcX,AcY,AcZ);

  //printing values to serial port
 // Serial.print("Angle: ");
 // Serial.print("Pitch = "); Serial.print(pitch);
 // Serial.print(" Roll = "); Serial.print(roll);
 // Serial.print(" Zpitch = "); Serial.print(zeroPitch);
 // Serial.print(" Zroll = "); Serial.println(zeroRoll);

  if (alt < 13){
   leftServo.write(45);   // sets the servo position
   rightServo.write(-45); // sets the servo position
   digitalWrite(buzzPin, HIGH);
  }else{
   leftServo.write(roll);   // sets the servo position
   rightServo.write(-roll); // sets the servo position
   digitalWrite(buzzPin, LOW);
  }  

  distance = getDistance(trigPin, echoPin);
  Serial.println(distance);

  delay(10);
}

