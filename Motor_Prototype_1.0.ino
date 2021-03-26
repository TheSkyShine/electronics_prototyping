
// Include Libraries
#include "Arduino.h"
#include "Servo.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"


// Pin Definitions
#define SERVO9G_PIN_SIG  2

/////////////////////////////////////////////////////////////////
// Sensor Initialization and Boolean Testing ////////////////////
/////////////////////////////////////////////////////////////////

#include "SparkFun_VCNL4040_Arduino_Library.h"
VCNL4040 proximitySensor;

long startingProxValue = 0;
long deltaNeeded = 0;
boolean nothingThere = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("SparkFun VCNL4040 Example");

  Wire.begin(); //Join i2c bus

  if (proximitySensor.begin() == false)
  {
    Serial.println("Device not found. Please check wiring.");
    while (1); //Freeze!
  }

  //Set the current used to drive the IR LED - 50mA to 200mA is allowed.
  proximitySensor.setLEDCurrent(200); //For this example, let's do max.

  //The sensor will average readings together by default 8 times.
  //Reduce this to one so we can take readings as fast as possible
  proximitySensor.setProxIntegrationTime(8); //1 to 8 is valid

  //Take 8 readings and average them
  for(byte x = 0 ; x < 8 ; x++)
  {
    startingProxValue += proximitySensor.getProximity();
  }
  startingProxValue /= 8;

  deltaNeeded = (float)startingProxValue * 0.05; //Look for 5% change
  if(deltaNeeded < 5) deltaNeeded = 5; //Set a minimum
}

void loop()
{
  unsigned int proxValue = proximitySensor.getProximity(); 

  Serial.print("Prox: ");
  Serial.print(proxValue);
  Serial.print(" ");

  //Let's only trigger if we detect a 5% change from the starting value
  //Otherwise, values at the edge of the read range can cause false triggers
  if(proxValue > (startingProxValue + deltaNeeded))
  {
    Serial.print("Something is there!");
    nothingThere = false;
  }
  else
  {
    if(nothingThere == false) Serial.print("I don't see anything");
    nothingThere = true;
  }

  Serial.println();
  delay(10);
}



// Global variables and defines
const int servo9gRestPosition   = 0;  //Starting position
const int servo9gTargetPosition = 150; //Position when event is detected
// object initialization
Servo servo9g;


// define vars for testing menu
// const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    servo9g.attach(SERVO9G_PIN_SIG);
    servo9g.write(servo9gRestPosition);
    delay(100);
    servo9g.detach();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // 9G Micro Servo - Test Code
    // The servo will rotate to target position and back to resting position with an interval of 500 milliseconds (0.5 seconds) 
    servo9g.attach(SERVO9G_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo9g.write(servo9gTargetPosition);  // 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(500);                              // 3. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servo9g.write(servo9gRestPosition);    // 4. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
    delay(500);                              // 5. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servo9g.detach();                    // 6. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }

    if(menuOption == '2') 
    {
      menuOption = menu();
      servo9g.detach();
    }
    
//    if (millis() - time0 > timeout)
//    {
//       menuOption = menu();
//    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

//    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("Press 1 to activate 9G Micro Servo"));
    Serial.println(F("Press 2 to stop \n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing 9G Micro Servo"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
