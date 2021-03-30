
// Include Libraries
#include "Arduino.h"
#include "Servo.h"


// Pin Definitions
#define SERVO360MICRO1_1_PIN_SIG  2
#define SERVO360MICRO2_2_PIN_SIG  3



// Global variables and defines

// object initialization
Servo servo360Micro1_1;
Servo servo360Micro2_2;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;
boolean cat = false;
int motor2_counter = 0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Continuous Rotation Micro Servo - FS90R #1 - Test Code
    // The servo will rotate CW in full speed, CCW in full speed, and will stop  with an interval of 2000 milliseconds (2 seconds) 
    servo360Micro1_1.attach(SERVO360MICRO1_1_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo360Micro1_1.write(180);  // 2. turns servo CW in full speed. change the value in the brackets (180) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 3. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro1_1.write(0);    // 4. turns servo CCW in full speed. change the value in the brackets (0) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 5. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro1_1.write(90);    // 6. sending 90 stops the servo 
    delay(2000);                              // 7. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro1_1.detach();                    // 8. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    
    motor2_counter++;
    }
    
    if(motor2_counter % 2 == 0) {  // turns treat motor every time the first motor is rotated X amount
    // if (millis() > 60000)  // if we'd rather use time as a basis for the treat dispenser instead of number of interactions
    // Continuous Rotation Micro Servo - FS90R #2 - Test Code
    // The servo will rotate CW in full speed, CCW in full speed, and will stop  with an interval of 2000 milliseconds (2 seconds) 
    servo360Micro2_2.attach(SERVO360MICRO2_2_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo360Micro2_2.write(100);  // 2. turns servo CW in full speed. change the value in the brackets (180) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 3. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro2_2.write(90);    // 4. turns servo CCW in full speed. change the value in the brackets (0) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(1000);                              // 5. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro2_2.write(80);    // 6. sending 90 stops the servo 
    delay(2000);                              // 7. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro2_2.detach();                    // 8. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    
//    if (millis() - time0 > timeout)
//    {
//        menuOption = menu();
//    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Continuous Rotation Micro Servo - FS90R #1"));
    Serial.println(F("(2) Continuous Rotation Micro Servo - FS90R #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing Continuous Rotation Micro Servo - FS90R #1"));
        else if(c == '2') 
          Serial.println(F("Now Testing Continuous Rotation Micro Servo - FS90R #2"));
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
