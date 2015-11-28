/*
MIYbot Test Program

6/23/13
1.0 8/13/13 - includes us,line sensor, motor, led and tone test.

YOU MUST INSTALL THE QTRSensors, NewPing and NewTone libraries!
google it!

10/4/13
So this program is one that will be used for testing and other things
hold USW1 down when it starts to get to the test program
hold USW2 down when it starts to do line following
hold nothing down and the bot will wait for you to hit one of the switches to start it in sumo mode!

2/3/2014
Working on makeing this software more generic and cleaning up the code.

9/9/14 rewrite so the bot is an object.  The two files are MIYbot.cpp and MIYbot.h

1/19/15 Added newTone and sounds, cleaned up colors and RGB
9/1/15 redid software to use servos
11/24/15 reworked to use the name MIYbot instead of BaxterBot

*/

#include "MIYbot.h"
#include <QTRSensors.h>
#include <NewPing.h>
#include <TimerFreeTone.h>
#include <stdio.h>
#include <Servo.h>  // SoftwareServo (works on non PWM pins)

        
MIYbot MB;
int mode = 0;  //mode 0 is the start mode



//  Please edit the following procedures to make your robot do what you want it to do.
//  Check the last few proceures if you want some hints as to how to run the motors or play a song
//  or something.

//************************************************************************************************
//
// RED - Drive around with ultrasonics
//
//************************************************************************************************
void Red(){
  Serial.println("Red");
  unsigned int uS_R;
  unsigned int uS_L;
  
  //thresholds
  int LineThreshold = 1000;
  int PingThreshold = 600;
  int tmpspeed = SLOW;
  int backspeed = SUPER_SLOW;

  while(!MB.button2_is_pressed()){
     uS_R = MB.usPing_R(); // Send ping, get ping time in microseconds (uS).
     uS_L = MB.usPing_L(); // Send ping, get ping time in microseconds (uS).
     Serial.print("Ultrasonic sensors L: ");
     Serial.print(uS_L);
     Serial.print("\tR: ");
     Serial.println(uS_R);
     
     if (uS_R < PingThreshold && uS_R != 0) {
        MB.setRGB(255, 0, 0);
        MB.MotorRun(2,backspeed, true);
        MB.MotorRun(3,backspeed, false);
        delay(500);
        MB.setRGB(0, 0, 0);
        delay(50);
     }    
     if (uS_L < PingThreshold && uS_L != 0) {
        MB.setRGB(0, 255, 0);
        MB.MotorRun(2,backspeed, false);
        MB.MotorRun(3,backspeed, true);
        delay(500);
        MB.setRGB(0, 0, 0);
        delay(50);   
     }
      MB.forward(tmpspeed);
  }
  MB.setColor(RED);
  
};

//************************************************************************************************
//
// Orange - test ultrasonics
//
//************************************************************************************************
void Orange() {
  Serial.println("Orange");
  unsigned int uS_R;
  unsigned int uS_L;
  //thresholds
  int LineThreshold = 1000;
  int PingThreshold = 1200;
  int r = 0;
  int g = 0;
  int b = 0;

  while(!MB.button2_is_pressed()){
     r = 0;
     g = 0;
     b = 0;
  
     uS_R = MB.usPing_R(); // Send ping, get ping time in microseconds (uS).
     uS_L = MB.usPing_L(); // Send ping, get ping time in microseconds (uS).
     Serial.print("Ultrasonic sensors L: ");
     Serial.print(uS_L);
     Serial.print("\tR: ");
     Serial.println(uS_R);
     
     if (uS_R < PingThreshold && uS_R != 0) {
        r=100;
     }    
     if (uS_L < PingThreshold && uS_L != 0) {
        b=100;
     }
     MB.setRGB(r,g,b);
  }
  MB.setColor(ORANGE);
  
};


//************************************************************************************************
//
// YELLOW - Test Line Sensors
//
//************************************************************************************************
void Yellow() {
  Serial.println("Yellow");
  int LineThreshold = 750;
  
  QTRSensorsRC qtrrc((unsigned char[]) {LINE_SENSOR_LEFT, LINE_SENSOR_RIGHT},  2, 2048, QTR_NO_EMITTER_PIN); 
  unsigned int sensorValues[2];  //variable for line sensors

  int r = 0;
  int g = 0;
  int b = 0;
  
  MB.setRGB(r,g,b);
  while(!MB.button2_is_pressed()){
     r = 0;
     g = 0;
     b = 0;
     
     qtrrc.read(sensorValues);
     
     if (sensorValues[0] <LineThreshold) {
        r=100;
     }    
     if (sensorValues[1] <LineThreshold) {
        b=100;
     }
     MB.setRGB(r,g,b);
  }
  MB.setColor(YELLOW);
};



//************************************************************************************************
//
// GREEN - SUMOBOT FIGHT!!!
//
//************************************************************************************************
void Green() {
  Serial.println("Green");
  //MB.setTrim(10);
  while(!MB.button2_is_pressed()){
      MB.setRGB(0, 255, 0);
  }
};

//************************************************************************************************
//
// BLUE - WHAT DOES THIS PROC DO?
//
//************************************************************************************************
void Blue() {
  Serial.println("Blue");
  MB.setColor(BLUE);
};

//************************************************************************************************
//
// DESCRIPTION - WHAT DOES THIS PROCEDURE DO???
//
//************************************************************************************************  
void Purple(){
  Serial.println("Purple");
  
} 

//************************************************************************************************
//
// WHITE - 
//
//************************************************************************************************
void White() {
  Serial.println("White"); 
};

//************************************************************************************************
//
// PINK - Test the line sensors
//
//************************************************************************************************
void Pink() {
  
  Serial.println("Pink");
  MB.setColor(PINK);
	  
};

//************************************************************************************************
//
// Play shave and a haircut
//
//************************************************************************************************
void Aqua() {
  Serial.println("Aqua");
  
  // Melody (liberated from the toneMelody Arduino example sketch by Tom Igoe).
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
      TimerFreeTone(BUZZER, melody[thisNote], noteDuration);
       
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
};





//===========================================================================//
//arduino setup and loop functions
//don't mess with this code!

        
void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("MIYbot program");
  MB.setup();
  
  MB.setRGB(0,0,255);
  delay(200);
  MB.setRGB(0,0,0);
  delay(200);
  MB.setRGB(0,255,0);
  delay(200);
  MB.setRGB(0,0,0);
  delay(200);
  MB.setRGB(255,0,0);
  
  // start mode red
  mode = 1;
  MB.setServoConfiguration(2);
  MB.beep();
  MB.beep();
}

void loop() {
  
  if (MB.button1_is_pressed()) {
     mode = mode +1;
     if (mode == 10) mode = 1;
     switch (mode) {
     case 1: 
       MB.beep();
       MB.beep();
       MB.setColor(RED);
       break; 
     case 2:  
       MB.beep();
       MB.setColor(ORANGE);
       break;
     case 3:  
       MB.beep();
       MB.setColor(YELLOW);
       break;
     case 4: 
       MB.beep();
       MB.setColor(GREEN);
       break;
     case 5:  
       MB.beep();
       MB.setColor(BLUE);
       break;
     case 6:
       MB.beep();
       MB.setColor(PURPLE);
       break;
     case 7:
       MB.beep();
       MB.setColor(WHITE);
       break;
     case 8:
       MB.beep(); 
       MB.setColor(PINK);
       break;
     case 9:
       MB.beep();
       MB.setColor(AQUA);
       break;
     }

     
  }
  else if ( MB.button2_is_pressed()) {
     //MB.beep();
     //MB.beep();

     switch (mode) {
     case 1:
       Red();
       break;
       
     case 2:
       Orange();
      break;
      
     case 3:
        Yellow();
        break;
        
     case 4:
       Green();
       break;
     
     case 5:
       Blue();
       break;
       
     case 6:
       Purple();
       break;
       
     case 7:
       White();
       break;
       
      case 8:
       Pink();
       break;
       
      case 9:
       Aqua();
       break;
     }
    
  }
  

}

