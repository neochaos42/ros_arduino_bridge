/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/



#ifdef CYTRON_DRIVER
  #define FRONT_RIGHT_MOTOR_PWM 10
  #define FRONT_LEFT_MOTOR_PWM 12
  #define FRONT_RIGHT_MOTOR_DIRECTION 11
  #define FRONT_LEFT_MOTOR_DIRECTION 13
  #define BACK_RIGHT_MOTOR_PWM 10
  #define BACK_LEFT_MOTOR_PWM 12
  #define BACK_RIGHT_MOTOR_DIRECTION 11
  #define BACK_LEFT_MOTOR_DIRECTION 13
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int frontLeftSpeed, int frontRightSpeed, int backLeftSpeed, int backRightSpeed);
