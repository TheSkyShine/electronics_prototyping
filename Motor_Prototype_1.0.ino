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

VCNL4040 proximitySensor1;
VCNL4040 proximitySensor2;

boolean somethingthere = false;
int motor2_counter = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("Begin the test");
  Wire.begin();

  if (proximitySensor1.begin() == false)
  {
    Serial.println("Sensor 1 not connected");
    while (1);
  }

  if (proximitySensor2.begin() == false)
  {
    Serial.println("Sensor 2 not connected");
    while (1);
  }
  
  proximitySensor1.setLEDCurrent(200);
  proximitySensor1.setProxIntegrationTime(8);

  proximitySensor2.setLEDCurrent(200);
  proximitySensor2.setProxIntegrationTime(8);
}

void loop() {
  unsigned int proxValue1 = proximitySensor1.getProximity();
  unsigned int proxValue2 = proximitySensor2.getProximity();

  Serial.print("I don't see anything");

  if((proxValue1 > 1) || (proxValue2 > 1) )
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

  if(somethingthere == true){
    servo360Micro1_1.attach(SERVO360MICRO1_1_PIN_SIG);
    servo360Micro1_1.write(180);
    delay(2000);
    servo360Micro1_1.write(0);
    delay(2000);
    servo360Micro1_1.write(90);
    delay(2000);
    servo360Micro1_1.detach();

    motor2_counter++;
  }

  if(millis() > 1000 && millis() < 11000) {
    servo360Micro2_2.attach(SERVO360MICRO2_2_PIN_SIG);
    servo360Micro2_2.write(110);
    delay(1000);
    servo360Micro2_2.write(90);
    delay(100);
    servo360Micro2_2.write(70);
    delay(1000);
    servo360Micro2_2.detach(); 
  }

  
}
