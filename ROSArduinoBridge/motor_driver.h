/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/


#ifdef DFROBOT_DRIVER
#define RIGHT_MOTOR_ENABLE 10
#define LEFT_MOTOR_ENABLE 11
#define RIGHT_MOTOR_DIRECTION 12
#define LEFT_MOTOR_DIRECTION 13
#elif defined(CYTRON_DRIVER)
#define RIGHT_MOTOR_PWM 10
#define LEFT_MOTOR_PWM 12
#define RIGHT_MOTOR_DIRECTION 11
#define LEFT_MOTOR_DIRECTION 13
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
