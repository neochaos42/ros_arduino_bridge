/* *************************************************************
   Encoder definitions

   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   ************************************************************ */

#ifdef USE_BASE


#ifdef ONBOARD_ENC_COUNTER
#include <Encoder.h>
Encoder encFrontLeft(FRONT_LEFT_ENC_PIN_A , FRONT_LEFT_ENC_PIN_B);
Encoder encFrontRight(FRONT_RIGHT_ENC_PIN_A , FRONT_RIGHT_ENC_PIN_B);
Encoder encBackLeft(BACK_LEFT_ENC_PIN_A , BACK_LEFT_ENC_PIN_B);
Encoder encBackRight(BACK_RIGHT_ENC_PIN_A , BACK_RIGHT_ENC_PIN_B);
volatile long positionFrontLeft = -999;
volatile long positionFrontRight = -999;
volatile long positionBackLeft = -999;
volatile long positionBackRight = -999;
long readEncoder(int i){
    if(i == FRONT_LEFT){
        long newPositionFrontLeft = encFrontLeft.read();
        if(newPositionFrontLeft != positionFrontLeft){
            positionFrontLeft = newPositionFrontLeft;
        }return newPositionFrontLeft;
    } else if(i == FRONT_RIGHT){
        long newPositionFrontRight = encFrontRight.read();
        if(newPositionFrontRight != positionFrontRight){
            positionFrontRight = newPositionFrontRight;
        }return newPositionFrontRight;
    } if(i == BACK_LEFT){
        long newPositionBackLeft = encBackLeft.read();
        if(newPositionBackLeft != positionBackLeft){
            positionBackLeft = newPositionBackLeft;
        }return newPositionBackLeft;
    } else{
        long newPositionBackRight = encBackRight.read();
        if(newPositionBackRight != positionBackRight){
            positionBackRight = newPositionBackRight;
        }return newPositionBackRight;
    }
}
  /* Wrap the encoder reset function */
void resetEncoder(int i){
    if(i == FRONT_LEFT){
        positionFrontLeft = 0L;
        encFrontLeft.write(0);
        return;
    } else if (i == FRONT_RIGHT){
        positionFrontRight = 0L;
        encFrontRight.write(0);
        return;
    } else if(i == BACK_LEFT){
        positionBackLeft = 0L;
        encBackLeft.write(0);
        return;
    } else{
        positionBackRight = 0L;
        encBackRight.write(0);
        return;
    }
}
#else
#error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders(){
    resetEncoder(FRONT_LEFT);
    resetEncoder(FRONT_RIGHT);
    resetEncoder(BACK_LEFT);
    resetEncoder(BACK_RIGHT);
}

#endif
