/***************************************************************
   Motor driver definitions

   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   *************************************************************/

#ifdef USE_BASE

#ifdef DFROBOT_DRIVER
void initMotorController(){
    digitalWrite(LEFT_MOTOR_ENABLE, LOW);
    pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
    pinMode(LEFT_MOTOR_DIRECTION, OUTPUT);
    digitalWrite(RIGHT_MOTOR_ENABLE, LOW);
    pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
    pinMode(RIGHT_MOTOR_DIRECTION, OUTPUT);
}

void setMotorSpeed(int i, int spd){
    unsigned char reverse = 0;

    if(spd < 0){
        spd = -spd;
        reverse = 1;
    }
    if(spd > 255)
        spd = 255;
    if(i == LEFT){
        if(reverse == 0){
            digitalWrite(LEFT_MOTOR_DIRECTION, LOW);
        } else if(reverse == 1){
            digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
        }analogWrite(LEFT_MOTOR_ENABLE, spd);
    } else /*if (i == RIGHT) //no need for condition*/{
        if(reverse == 0){
            digitalWrite(RIGHT_MOTOR_DIRECTION, LOW);
        } else if(reverse == 1){
            digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
        }analogWrite(RIGHT_MOTOR_ENABLE, spd);
    }
}
void setMotorSpeeds(int leftSpeed, int rightSpeed){
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
}
#elif defined(CYTRON_DRIVER)
#include "CytronMotorDriver.h"
CytronMD leftMotor(PWM_DIR, LEFT_MOTOR_PWM, LEFT_MOTOR_DIRECTION);  // PWM 1 = Pin 3, DIR 1 = Pin 4.
CytronMD rightMotor(PWM_DIR, RIGHT_MOTOR_PWM, RIGHT_MOTOR_DIRECTION); // PWM 2 = Pin 9, DIR 2 = Pin 10.
void initMotorController(){}
void setMotorSpeed(int i, int spd){
    if(i == LEFT){
        leftMotor.setSpeed(spd);
    } else{
        rightMotor.setSpeed(spd);
    }
}
void setMotorSpeeds(int leftSpeed, int rightSpeed){
    leftMotor.setSpeed(leftSpeed);
    rightMotor.setSpeed(rightSpeed);
}
#else
#error A motor driver must be selected!
#endif

#endif
