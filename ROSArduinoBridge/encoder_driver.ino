/* *************************************************************
   Encoder definitions

   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   ************************************************************ */

#ifdef USE_BASE


#ifdef ONBOARD_ENC_COUNTER
#include "QuadratureEncoder.h"
uint8_t pinsA[4] = { FRONT_LEFT_ENC_PIN_A, FRONT_RIGHT_ENC_PIN_A, BACK_LEFT_ENC_PIN_A, BACK_RIGHT_ENC_PIN_A };
uint8_t pinsB[4] = { FRONT_LEFT_ENC_PIN_B, FRONT_RIGHT_ENC_PIN_B, BACK_LEFT_ENC_PIN_B, BACK_RIGHT_ENC_PIN_B };
uint8_t encoderCount = 4;  // Number of encoders

QuadratureEncoder encoder(pinsA, pinsB, encoderCount);
volatile long positionFrontLeft = -999;
volatile long positionFrontRight = -999;
volatile long positionBackLeft = -999;
volatile long positionBackRight = -999;
void setupEncoder() {
  encoder.begin();
}
long readEncoder(int encoderID) {
  long newPosition = 0;

  switch (encoderID) {
    case FRONT_LEFT:
      newPosition = encoder.getPosition(FRONT_LEFT);
      if (newPosition != positionFrontLeft) {
        positionFrontLeft = newPosition;
      }
      break;
    case FRONT_RIGHT:
      newPosition = encoder.getPosition(FRONT_RIGHT);
      if (newPosition != positionFrontRight) {
        positionFrontRight = newPosition;
      }
      break;
    case BACK_LEFT:
      newPosition = encoder.getPosition(BACK_LEFT);
      if (newPosition != positionBackLeft) {
        positionBackLeft = newPosition;
      }
      break;
    case BACK_RIGHT:
      newPosition = encoder.getPosition(BACK_RIGHT);
      if (newPosition != positionBackRight) {
        positionBackRight = newPosition;
      }
      break;
    default:
      // Handle invalid encoder ID
      Serial.println("Invalid encoder ID");
      return -1;  // Indicate error
  }

  return newPosition;
}

// Function to reset a specific encoder
void resetEncoder(int encoderID) {
  switch (encoderID) {
    case FRONT_LEFT:
      positionFrontLeft = 0L;
      encoder.reset(FRONT_LEFT);
      break;
    case FRONT_RIGHT:
      positionFrontRight = 0L;
      encoder.reset(FRONT_RIGHT);
      break;
    case BACK_LEFT:
      positionBackLeft = 0L;
      encoder.reset(BACK_LEFT);
      break;
    case BACK_RIGHT:
      positionBackRight = 0L;
      encoder.reset(BACK_RIGHT);
      break;
    default:
      // Handle invalid encoder ID
      Serial.println("Invalid encoder ID");
      break;
  }
}
#else
#error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(FRONT_LEFT);
  resetEncoder(FRONT_RIGHT);
  resetEncoder(BACK_LEFT);
  resetEncoder(BACK_RIGHT);
}

#endif
