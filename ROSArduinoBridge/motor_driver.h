/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/



#ifdef CYTRON_DRIVER
#define FRONT_LEFT_MOTOR_PWM 9 
#define FRONT_LEFT_MOTOR_DIRECTION 8

#define FRONT_RIGHT_MOTOR_PWM 7
#define FRONT_RIGHT_MOTOR_DIRECTION 6

#define BACK_LEFT_MOTOR_PWM 13
#define BACK_LEFT_MOTOR_DIRECTION 12

#define BACK_RIGHT_MOTOR_PWM 11
#define BACK_RIGHT_MOTOR_DIRECTION 10

#endif

void initMotorController();
void setMotorSpeed(int motorID, int spd);
void setMotorSpeeds(int frontLeftSpeed, int frontRightSpeed, int backLeftSpeed, int backRightSpeed);
