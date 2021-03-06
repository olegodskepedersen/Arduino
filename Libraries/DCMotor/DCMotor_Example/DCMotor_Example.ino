// Scott Camarena
// scprojects.wordpress.com
// November 2012
// Lang: Arduino C++
// DC Motor Class
//=============================================================

#include "DCMotor.h"

DCMotor motor1( 3, 5 );
DCMotor motor2( 9, 10 );
int mspeed = 0;    // motor speed
int fadeAmount = 5;    // how many points to adjust speed by
void setup()
{
  
}

void loop()
{
  // Speed up
  while(mspeed < 255)
  {
    motor1.on(mspeed);
    motor2.back(mspeed);
    // change the brightness for next time through the loop:
    mspeed = mspeed + fadeAmount;
    delay(30);
  }
  delay(100);
  
  // Slow down
  while(mspeed > 0)
  {
    motor1.on(mspeed);
    motor2.back(mspeed);
    // change the brightness for next time through the loop:
    mspeed = mspeed - fadeAmount;
    delay(30);
  }
  motor1.off();
  delay(50);
  
  // Speed up backwards
  while(mspeed < 255)
  {
    motor1.back(mspeed);
    motor2.on(mspeed);
    // change the brightness for next time through the loop:
    mspeed = mspeed + fadeAmount;
    delay(30);
  }
  delay(100);
  
  // Slow down
  while(mspeed > 0)
  {
    motor1.back(mspeed);
    motor2.on(mspeed);
    // change the brightness for next time through the loop:
    mspeed = mspeed - fadeAmount;
    delay(30);
  }
  motor1.off();
  delay(100);
}
