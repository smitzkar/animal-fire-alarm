/* 
To create audio: https://ttsmaker.com/
DFPlayer module supports up to 3W. 
SD card: 2GB ~ 32GB formatted with FAT or FAT32. 
MP3 / WAV - audio files. 
*/

#include "SoftwareSerial.h"         // Include the SoftwareSerial library for serial communication
#include "DFRobotDFPlayerMini.h"    // Include the DFRobotDFPlayerMini library for the DFPlayer Mini module

SoftwareSerial mySoftwareSerial(10, 11); // Create a software serial connection on pins 10 (RX) and 11 (TX)
DFRobotDFPlayerMini myDFPlayer;          // Create a DFPlayerMini object

const int pushButtonPin = 2;        // Define the pin number for the push button
bool buttonState;                   // Variable to store the state of the button
bool wasButtonPressed = false;      // Flag to track whether the button was previously pressed

void setup() {
  mySoftwareSerial.begin(9600);     // Start software serial communication at 9600 baud rate
  Serial.begin(115200);             // Start serial communication at 115200 baud rate
  pinMode(pushButtonPin, INPUT_PULLUP); // Set push button pin as input with internal pull-up resistor
  
  if (!myDFPlayer.begin(mySoftwareSerial)) { // Initialize the DFPlayer Mini module
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true);                  // If initialization fails, print error messages and halt the program
  }
  
  Serial.println();
  Serial.println(F("DFPlayer Mini module initialized!")); // Print initialization success message
  myDFPlayer.setTimeOut(500);       // Set the timeout value for serial communication
  myDFPlayer.volume(30);            // Set the volume level (0 to 30)
  myDFPlayer.EQ(0);                 // Set the equalizer setting (0: Normal, 1: Pop, 2: Rock, 3: Jazz, 4: Classic, 5: Bass)
}

void loop() {
  buttonState = digitalRead(pushButtonPin); // Read the state of the button

  if (buttonState == LOW) {          // If the button is pressed (assuming pull-up configuration)
    if (!wasButtonPressed) {         // If the button was not previously pressed
      Serial.println("Playing song 1");
      myDFPlayer.next();            // Play the next audio file on the SD card
      delay(2000);                   // Delay for 2 seconds

      wasButtonPressed = true;       // Set the flag to true to indicate that the button was pressed
    }
  } else {                           // If the button is not pressed
    Serial.println("Push button not pressed");
    wasButtonPressed = false;        // Reset the flag when the button is released
  }
}
