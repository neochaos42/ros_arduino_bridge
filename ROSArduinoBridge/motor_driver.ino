/***************************************************************
   Motor driver definitions

   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   *************************************************************/

#ifdef USE_BASE

#ifdef CYTRON_DRIVER
#include "CytronMotorDriver.h"
CytronMD frontLeftMotor(PWM_DIR, FRONT_LEFT_MOTOR_PWM, FRONT_LEFT_MOTOR_DIRECTION);  // PWM 1 = Pin 3, DIR 1 = Pin 4.
CytronMD frontRightMotor(PWM_DIR, FRONT_RIGHT_MOTOR_PWM, FRONT_RIGHT_MOTOR_DIRECTION); // PWM 2 = Pin 9, DIR 2 = Pin 10.
CytronMD backLeftMotor(PWM_DIR, BACK_LEFT_MOTOR_PWM, BACK_LEFT_MOTOR_DIRECTION);  // PWM 1 = Pin 3, DIR 1 = Pin 4.
CytronMD backRightMotor(PWM_DIR, BACK_RIGHT_MOTOR_PWM, BACK_RIGHT_MOTOR_DIRECTION); // PWM 2 = Pin 9, DIR 2 = Pin 10.
void initMotorController(){}
void setMotorSpeed(int i, int spd){
    if(i == FRONT_LEFT){
        frontLeftMotor.setSpeed(spd);
    } else if(i == FRONT_RIGHT) {
        frontRightMotor.setSpeed(spd);
    }else if(i == BACK_RIGHT){
        backLeftMotor.setSpeed(spd);
    }else{
        backRightMotor.setSpeed(spd);
    }
}
void setMotorSpeeds(int frontLeftSpeed, int frontRightSpeed, int backLeftSpeed, int backRightSpeed){
    frontLeftMotor.setSpeed(frontLeftSpeed);
    frontRightMotor.setSpeed(frontRightSpeed);
    backLeftMotor.setSpeed(backLeftSpeed);
    backRightMotor.setSpeed(backRightSpeed);
}
#else
#error A motor driver must be selected!
#endif

#endif
