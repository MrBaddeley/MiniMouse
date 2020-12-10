#define CUSTOM_SETTINGS         //setting up Dabble
#define INCLUDE_GAMEPAD_MODULE  //setting up Dabble
#include <Dabble.h>             //setting up Dabble

#include "Arduino.h"             //DFplayer setup
#include "SoftwareSerial.h"      //DFplayer setup
#include "DFRobotDFPlayerMini.h" //DFplayer setup

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX  //Software serial for DFplayer (position B jumpers)
DFRobotDFPlayerMini myDFPlayer;          //Start the DFPlater
void printDetail(uint8_t type, int value); //DFPlayer subroutine

int speedA = 0; //Set up the speed for forward
int speedB = 0; //Set up the speed for reverse
int Steer =190; //Set default position for steering

void setup()
{
  mySoftwareSerial.begin(9600); //Starts software serial, using pins 10 and 11
  Serial.begin(115200); //Diagnostics Serial for screen print
  
 
  Serial.println(); //DF Player diagnostics / start up
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online.")); // DF Player online check
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30,30 max
  delay (1000); //Pause 1 second
  myDFPlayer.play(1);  //Play the first mp3 to confirm online

Dabble.begin(9600); 
}

void loop()
{

  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
 

  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
  Serial.print("KeyPressed: ");

if (d > -.05) {
 speedA= map(d,0,6,60,255);
 speedB=0;
}

if (d < .05) {
 speedB= map(-d,0,7,60,255);
 speedA=0;
}

if (d==0) {
speedA =0;
speedB=0;
}
Steer = map (c,-7,7,140,240);
analogWrite(5, speedA); //Drive forward is on pin 5
analogWrite(6, speedB); //Drive backwards is on pin 6
analogWrite (9,Steer); //Steer is on pin 9
  
if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }
 
  
 if (GamePad.isTrianglePressed())
 {
   Serial.print("Play first sound (Triange)");
   myDFPlayer.play(1); //play the first mp3
 }

if (GamePad.isCrossPressed())
 {
   Serial.print("Pause sounds(Cross)");
   myDFPlayer.pause();  //pause the mp3
 }
 
  Serial.println("");
  
}
