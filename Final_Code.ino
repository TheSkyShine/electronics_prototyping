// Libraries to be included so components can work
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "Arduino.h"
#include "Servo.h"

// Pin Definitions
#define SERVO360MICRO1_1_PIN_SIG  2
#define SERVO360MICRO2_2_PIN_SIG  3

// object initialization
Servo servo360Micro1_1;
Servo servo360Micro2_2;

VCNL4040 proximitySensor;
VCNL4040 proximitySensor2;
VCNL4040 proximitySensor3;
VCNL4040 proximitySensor4;

boolean somethingthere = false;
int motor2_counter = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("Begin the test");
  Wire.begin();

  if (proximitySensor.begin() == false)
  {
    Serial.println("Not connected");
    while (1);
  }

  if (proximitySensor2.begin() == false)
  {
    Serial.println("Not connected");
    while (1);
  }
  if (proximitySensor3.begin() == false)
  {
    Serial.println("Not connected");
    while (1);
  }
  if (proximitySensor4.begin() == false)
  {
    Serial.println("Not connected");
    while (1);
  }


  
  proximitySensor.setLEDCurrent(200);
  proximitySensor.setProxIntegrationTime(8);

  proximitySensor2.setLEDCurrent(200);
  proximitySensor2.setProxIntegrationTime(8);

  proximitySensor3.setLEDCurrent(200);
  proximitySensor3.setProxIntegrationTime(8);

  proximitySensor4.setLEDCurrent(200);
  proximitySensor4.setProxIntegrationTime(8);
}

void loop() {
  unsigned int proxValue = proximitySensor.getProximity();
  unsigned int proxValue2 = proximitySensor2.getProximity();
  unsigned int proxValue3 = proximitySensor3.getProximity();
  unsigned int proxValue4 = proximitySensor4.getProximity();

  Serial.print("I don't see anything");

  if(proxValue > 1 || proxValue2 > 1 || proxValue3 > 1 || proxValue4 > 1)                                 // If sensors seem too sensitive, increase beyond 1 but not above 3
  {
    Serial.print("\nSomething is there");
    somethingthere = true;
  }
  else
  {
    somethingthere = false;
  }

  Serial.println();
  delay(10);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Code for first motor

  if(somethingthere == true){                               // If any sensor senses anything, it activates this code and turns on the motor
    servo360Micro1_1.attach(SERVO360MICRO1_1_PIN_SIG);
    servo360Micro1_1.write(180);
    delay(1000);
    servo360Micro1_1.write(0);
    delay(1000);
    servo360Micro1_1.write(90);
    delay(1000);
    servo360Micro1_1.detach();

    motor2_counter++;                                        // Itercounter +1 for first motor (counts how many times the first motor has been turned on)
  }

// Code for second motor

  if(motor2_counter % 2 == 0 && motor2_counter !=1) {                             // Every 20 turns the first motor does, second motor turns
    servo360Micro2_2.attach(SERVO360MICRO2_2_PIN_SIG);       // Attaches into motor 2
    servo360Micro2_2.write(110);                             // Gives value of 110 PWM to sevo motor (will turn clockwise)
    delay(1000);                                             // The 110 PWM value will stay on the motor for 1000 ms (1 second)
    servo360Micro2_2.write(90);                              // Attaches value of 90 PWM to servo motor (90 PWM tells the servo to not move)
    delay(10);                                               // Servo does not move for 10 ms
    servo360Micro2_2.write(42);                              // Gives value of 70 PWM to servo motor (will turn counter-clockwise)
    delay(1000);                                             // Servo goes at 70 PWM for 100 ms (1 second)
    servo360Micro2_2.detach();                               // Detaches motor (end of instruction)
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
}

// Servo motors work between 0 and 180 PWM, where the PWM indicates the speed of the motor. 0 is max speed counter clockwise, 180 is max speed clockwise and 90 is no speed.
// Note this relationship is not linear, which is what gave me trouble. But you should be able to figure this out since you have the physical toy.
