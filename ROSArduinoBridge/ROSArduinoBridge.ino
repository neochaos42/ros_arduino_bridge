/*********************************************************************
 *  ROSArduinoBridge

    A set of simple serial commands to control a differential drive
    robot and receive back sensor and odometry data. Default
    configuration assumes use of an Arduino Mega + Pololu motor
    controller shield + Robogaia Mega Encoder shield.  Edit the
    readEncoder() and setMotorSpeed() wrapper functions if using
    different motor controller or encoder method.

    Created for the Pi Robot Project: http://www.pirobot.org
    and the Home Brew Robotics Club (HBRC): http://hbrobotics.org

    Authors: Patrick Goebel, James Nugen

    Inspired and modeled after the ArbotiX driver by Michael Ferguson

    Software License Agreement (BSD License)

    Copyright (c) 2012, Patrick Goebel.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above
       copyright notice, this list of conditions and the following
       disclaimer in the documentation and/or other materials provided
       with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#define USE_BASE      // Enable the base controller code
//#undef USE_BASE     // Disable the base controller code

/* Define the motor controller and encoder library you are using */
#ifdef USE_BASE

   /* Encoders directly attached to Arduino board */
#define ONBOARD_ENC_COUNTER

/* L298 Motor driver*/
#define CYTRON_DRIVER
#endif

//#define USE_SERVOS  // Enable use of PWM servos as defined in servos.h
#undef USE_SERVOS     // Disable use of PWM servos

/* Serial port baud rate */
#define BAUDRATE     57600

/* Maximum PWM signal */
#define MAX_PWM        255

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/* Include definition of serial commands */
#include "commands.h"

/* Sensor functions */
#include "sensors.h"

/* Include servo support if required */
#ifdef USE_SERVOS
#include <Servo.h>
#include "servos.h"
#endif

#ifdef USE_BASE
  /* Motor driver function definitions */
#include "motor_driver.h"

/* Encoder driver function definitions */
#include "encoder_driver.h"

/* PID parameters and functions */
#include "diff_controller.h"

/* Run the PID loop at 30 times per second */
#define PID_RATE           30     // Hz

/* Convert the rate into an interval */
const int PID_INTERVAL = 1000 / PID_RATE;

/* Track the next time we make a PID calculation */
unsigned long nextPID = PID_INTERVAL;

/* Stop the robot if it hasn't received a movement command
 in this number of milliseconds */
#define AUTO_STOP_INTERVAL 2000
long lastMotorCommand = AUTO_STOP_INTERVAL;
#endif

/* Variable initialization */

// A pair of variables to help parse serial commands (thanks Fergs)
int arg = 0;
int localIndex = 0;

// Variable to hold an input character
char chr;

// Variable to hold the current single-character command
char cmd;

// Character arrays to hold the arguments
char argv1[16];
char argv2[16];
char argv3[16];
char argv4[16];

// The arguments converted to integers
long arg1;
long arg2;
long arg3;
long arg4;

/* Clear the current command parameters */
void resetCommand(){
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  memset(argv3, 0, sizeof(argv3));
  memset(argv4, 0, sizeof(argv4));
  arg1 = 0;
  arg2 = 0;
  arg3 = 0;
  arg4 = 0;
  arg = 0;
  localIndex = 0;
}

/* Run a command.  Commands are defined in commands.h */
int runCommand(){
  int i = 0;
  char* p = argv1;
  char* str;
  int pid_args[4];

  // Convert args to integers
  arg1 = atoi(argv1);
  arg2 = atoi(argv2);
  arg3 = atoi(argv3);
  arg4 = atoi(argv4);

  switch(cmd){
    case GET_BAUDRATE:
      Serial.println(BAUDRATE);
      break;
    // ... [Other cases remain unchanged]

#ifdef USE_BASE
    case READ_ENCODERS:
      Serial.print(readEncoder(FRONT_LEFT));
      Serial.print(" ");
      Serial.print(readEncoder(FRONT_RIGHT));
      Serial.print(" ");
      Serial.print(readEncoder(BACK_LEFT));
      Serial.print(" ");
      Serial.println(readEncoder(BACK_RIGHT));
      break;
    case RESET_ENCODERS:
      resetEncoders();
      resetPID();
      Serial.println("OK");
      break;
    case MOTOR_SPEEDS:
      /* Reset the auto stop timer */
      lastMotorCommand = millis();
      if(arg1 == 0 && arg2 == 0 && arg3 == 0 && arg4 == 0){
        setMotorSpeeds(0, 0, 0, 0);
        resetPID();
        moving = 0;
      } else {
        moving = 1;
      }
      frontLeftPID.TargetTicksPerFrame = arg1;
      frontRightPID.TargetTicksPerFrame = arg2;
      backLeftPID.TargetTicksPerFrame = arg3;
      backRightPID.TargetTicksPerFrame = arg4;
      Serial.println("OK");
      break;
    case MOTOR_RAW_PWM:
      /* Reset the auto stop timer */
      lastMotorCommand = millis();
      resetPID();
      moving = 0; // Temporarily disable the PID
      setMotorSpeeds(arg1, arg2, arg3, arg4);
      Serial.println("OK");
      break;
    // ... [Rest of the cases remain unchanged]
#endif
    default:
      Serial.println("Invalid Command");
      break;
  }
}

/* Setup function--runs once at startup. */
void setup(){
  Serial.begin(BAUDRATE);

  // Initialize the motor controller if used
#ifdef USE_BASE
  initMotorController();
  resetPID();
  setupEncoder();

#endif
}

/* Enter the main loop.  Read and parse input from the serial port
   and run any valid commands. Run a PID calculation at the target
   interval and check for auto-stop conditions.
*/
void loop(){
  while(Serial.available() > 0){

    // Read the next character
    chr = Serial.read();

    // Terminate a command with a CR
    if(chr == 13){  // Carriage return
      if(arg == 1) argv1[localIndex] = NULL;
      else if(arg == 2) argv2[localIndex] = NULL;
      else if(arg == 3) argv3[localIndex] = NULL;
      else if(arg == 4) argv4[localIndex] = NULL;
      runCommand();
      resetCommand();
    }
    // Use spaces to delimit parts of the command
    else if(chr == ' '){
      // Step through the arguments
      if(arg == 0) arg = 1;
      else if(arg == 1){
        argv1[localIndex] = NULL;
        arg = 2;
        localIndex = 0;
      } else if(arg == 2){
        argv2[localIndex] = NULL;
        arg = 3;
        localIndex = 0;
      } else if(arg == 3){
        argv3[localIndex] = NULL;
        arg = 4;
        localIndex = 0;
      }
      continue;
    } else{
      if(arg == 0){
        // The first arg is the single-letter command
        cmd = chr;
      } else if(arg == 1){
        // Subsequent arguments can be more than one character
        argv1[localIndex] = chr;
        localIndex++;
      } else if(arg == 2){
        argv2[localIndex] = chr;
        localIndex++;
      } else if(arg == 3){
        argv3[localIndex] = chr;
        localIndex++;
      } else if(arg == 4){
        argv4[localIndex] = chr;
        localIndex++;
      }
    }
  }

#ifdef USE_BASE
  // If we are using base control, run a PID calculation at the appropriate intervals
  if(millis() > nextPID){
    updatePID();
    nextPID += PID_INTERVAL;
  }

  // Check to see if we have exceeded the auto-stop interval
  if((millis() - lastMotorCommand) > AUTO_STOP_INTERVAL){
    setMotorSpeeds(0, 0, 0, 0);
    moving = 0;
  }
#endif

// Sweep servos
#ifdef USE_SERVOS
  int i;
  for(i = 0; i < N_SERVOS; i++){
    servos[i].doSweep();
  }
#endif
}
