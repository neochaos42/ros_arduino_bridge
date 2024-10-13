/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */


#ifdef ONBOARD_ENC_COUNTER
  #define FRONT_LEFT_ENC_PIN_A 0 //good 7
  #define FRONT_LEFT_ENC_PIN_B 14 //good 14
  #define FRONT_RIGHT_ENC_PIN_A 3 //good 2
  #define FRONT_RIGHT_ENC_PIN_B 4 //good 8
  #define BACK_LEFT_ENC_PIN_A 18 //good 5
  #define BACK_LEFT_ENC_PIN_B 19 //good 6
  #define BACK_RIGHT_ENC_PIN_A 1 //good 9
  #define BACK_RIGHT_ENC_PIN_B 2 //good 3
#endif

long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

