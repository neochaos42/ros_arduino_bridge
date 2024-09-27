/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */


#ifdef ONBOARD_ENC_COUNTER
  #define FRONT_LEFT_ENC_PIN_A 18
  #define FRONT_LEFT_ENC_PIN_B 19
  #define FRONT_RIGHT_ENC_PIN_A 2
  #define FRONT_RIGHT_ENC_PIN_B 3
  #define BACK_LEFT_ENC_PIN_A 18
  #define BACK_LEFT_ENC_PIN_B 19
  #define BACK_RIGHT_ENC_PIN_A 2
  #define BACK_RIGHT_ENC_PIN_B 3
#endif

long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

