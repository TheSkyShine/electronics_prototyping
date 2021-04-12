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
  
  proximitySensor.setLEDCurrent(200);
  proximitySensor.setProxIntegrationTime(8);
}

void loop() {
  unsigned int proxValue = proximitySensor.getProximity();

  Serial.print("I don't see anything");

  if(proxValue > 1)
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

  //if(millis() > 60000 && millis() < 61000) {
  if(motor2_counter % 20 == 0) {
    servo360Micro2_2.attach(SERVO360MICRO2_2_PIN_SIG);
    servo360Micro2_2.write(110);
    delay(1000);
    servo360Micro2_2.write(90);
    delay(10);
    servo360Micro2_2.write(70);
    delay(1000);
    servo360Micro2_2.detach(); 
  }

  
}
