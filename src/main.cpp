
#include "Arduino.h"

// comment this line out to upload the blynk program
// otherwise this will upload an interactive program 
// where you can type in AT+... commands to configure
// the bluetooth module
#define SEND_AT_COMMANDS

#ifndef SEND_AT_COMMANDS

#define BLYNK_USE_DIRECT_CONNECT

//#define BLYNK_PRINT Serial
#include <BlynkSimpleSerialBLE.h>

char auth[] = "84b07fe5076841e58a59e7d88b356ddb";

BLYNK_WRITE(V1)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

    Serial.println(pinValue);
}

void setup()
{
    while(!Serial);
    // Blynk will work through Serial
    // Do not read or write this serial manually in your sketch
    Serial1.begin(115200);
    Blynk.begin(Serial1, auth);
}

void loop()
{
    Blynk.run();
}

#else

char c=' ';
boolean NL = true;
 
void setup() 
{
    Serial.begin(9600);
    while(!Serial);

    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    Serial1.begin(115200);  
    Serial.println("BTserial started at 9600");
}
 
void loop()
{
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    while (Serial1.available())
    {
        c = Serial1.read();
        Serial.write(c);
    }
 
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
 
        // do not send line end characters to the HM-10
        if (c!=10 & c!=13 ) 
        {  
             Serial1.write(c);
        }
 
        // Echo the user input to the main window. 
        // If there is a new line print the ">" character.
        if (NL) { Serial.print("\r\n>");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }
}

#endif