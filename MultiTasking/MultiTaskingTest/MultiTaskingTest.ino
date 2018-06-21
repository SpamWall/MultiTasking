/*
    Name:       MultiTaskingTest.ino
    Created:	6/20/2018 2:51:05 PM
    Author:     Craig Walters
*/


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <MultiTasking.h>

#define YELLOW_SEG_01  0
#define YELLOW_SEG_02  1
#define YELLOW_SEG_03  5
#define YELLOW_SEG_04  6
#define YELLOW_SEG_05  7
#define YELLOW_SEG_06  8
#define YELLOW_SEG_07  9
#define YELLOW_SEG_08 10
#define YELLOW_SEG_09 11
#define YELLOW_SEG_10 12
#define RED_LED       13
#define GREEN_LED_01  14
#define GREEN_LED_02  15
#define BUTTON_PIN    19


MultiTasking &timingController = *new MultiTasking(4);

struct working_memory
{
   bool    blinking = false;
   bool    redState = false;
   bool    greenState = false;
   uint8_t yellowState = 0;
} workingMemory;



bool blinkGreen() {
   workingMemory.greenState = !workingMemory.greenState;
   digitalWrite(GREEN_LED_01,  workingMemory.greenState);
   digitalWrite(GREEN_LED_02, !workingMemory.greenState);

   return false; // Allow the event chain to continue
}

bool scaleBar() {
   digitalWrite(YELLOW_SEG_01, LOW);
   digitalWrite(YELLOW_SEG_02, LOW);
   digitalWrite(YELLOW_SEG_03, LOW);
   digitalWrite(YELLOW_SEG_04, LOW);
   digitalWrite(YELLOW_SEG_05, LOW);
   digitalWrite(YELLOW_SEG_06, LOW);
   digitalWrite(YELLOW_SEG_07, LOW);
   digitalWrite(YELLOW_SEG_08, LOW);
   digitalWrite(YELLOW_SEG_09, LOW);
   digitalWrite(YELLOW_SEG_10, LOW);

   switch (workingMemory.yellowState) {
      case 10:  digitalWrite(YELLOW_SEG_10, HIGH);
      case  9:  digitalWrite(YELLOW_SEG_09, HIGH);
      case  8:  digitalWrite(YELLOW_SEG_08, HIGH);
      case  7:  digitalWrite(YELLOW_SEG_07, HIGH);
      case  6:  digitalWrite(YELLOW_SEG_06, HIGH);
      case  5:  digitalWrite(YELLOW_SEG_05, HIGH);
      case  4:  digitalWrite(YELLOW_SEG_04, HIGH);
      case  3:  digitalWrite(YELLOW_SEG_03, HIGH);
      case  2:  digitalWrite(YELLOW_SEG_02, HIGH);
      case  1:  digitalWrite(YELLOW_SEG_01, HIGH);
      default:
         break;
   }

   if(workingMemory.yellowState == 10) {
      workingMemory.yellowState = 0;
   } else    {
      ++workingMemory.yellowState;
   }

   return false;  // Allow the event chain to continue
}

bool blinkRed()
{
   workingMemory.redState = !workingMemory.redState;  // Switch light states
   digitalWrite(RED_LED, workingMemory.redState);     // Display the state

   return false;                                      // Allow the event chain to continue
}

bool buttonPressed()
{
   return true;
}


void setup()
{
   pinMode(YELLOW_SEG_01, OUTPUT);
   pinMode(YELLOW_SEG_02, OUTPUT);
   pinMode(YELLOW_SEG_03, OUTPUT);
   pinMode(YELLOW_SEG_04, OUTPUT);
   pinMode(YELLOW_SEG_05, OUTPUT);
   pinMode(YELLOW_SEG_06, OUTPUT);
   pinMode(YELLOW_SEG_07, OUTPUT);
   pinMode(YELLOW_SEG_08, OUTPUT);
   pinMode(YELLOW_SEG_09, OUTPUT);
   pinMode(YELLOW_SEG_10, OUTPUT);

   pinMode(RED_LED, OUTPUT);

   pinMode(GREEN_LED_01, OUTPUT);
   pinMode(GREEN_LED_02, OUTPUT);

   pinMode(BUTTON_PIN, INPUT);

   timingController.addListener(new TimerEventListener(1000, true, reinterpret_cast<EventAction>(blinkGreen)));
   timingController.addListener(new TimerEventListener( 300, true, reinterpret_cast<EventAction>(scaleBar)));
   timingController.addListener(new TimerEventListener( 200, true, reinterpret_cast<EventAction>(blinkRed)));
   timingController.addListener(new PinEventListener  (BUTTON_PIN, reinterpret_cast<EventAction>(buttonPressed)));
}

USE_MULTITASKING_LOOP(timingController)
