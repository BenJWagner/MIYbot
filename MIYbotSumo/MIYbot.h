#ifndef MIYbot_h
#define MIYbot_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*
MIYbot Object
Brian Wagner
9/9/14
11/24/15
*/

#include <QTRSensors.h>
#include <NewPing.h>
#include <TimerFreeTone.h>
#include <stdio.h>
#include <Servo.h>  



//===========================================================================//
// pin Definitions for the MIYbot
// rgb led pins
#define LED_R  3 
#define LED_G 5  
#define LED_B 6 
#define TEST_LED 13

//Servo pins
#define SERVO_A 9  //aux motor
#define SERVO_B 10  //left motor
#define SERVO_C 11  //right motor

//motor speed defines
#define SUPER_SLOW 10
#define SLOW 20
#define MEDIUM 30
#define FAST 40
#define SUPER_FAST 50

// Buzzer pin
#define BUZZER 4

//input pins for the switches
#define SW_1 14
#define SW_2 15

//line sensor pins
#define LINE_SENSOR_LEFT 12
#define LINE_SENSOR_RIGHT 8

//ultra sonic sensor pins - center pins
#define L_TRIGGER_PIN 16  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define L_ECHO_PIN 16  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define R_TRIGGER_PIN 17
#define R_ECHO_PIN 17

#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//notes to use
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//colors for setColor!
#define OFF 0
#define YELLOW 1
#define ORANGE 2
#define RED 3
#define BLUE 4
#define PINK 5
#define PURPLE 6
#define GREEN 7
#define WHITE 9
#define DIMWHITE 10
#define AQUA 11

class MIYbot{
public:

  void setup();
  void setMotorSpeed(uint8_t speed);
  
  //buzzer functions
  void beep();
  void hibeep();
  void lowbeep();
  void playNote(int note, int note_len);
  void rest(int note_len);
  void setTempo(int tempo);
  void sumoCountdown(int count);
  
  //movement
  void forward(int delay);
  void reverse(int delay);
  void MotorRun(int servo, int pwm_speed, boolean reverse);
  void spin(int delay, boolean reverse);
  void motorStop();
  void motorCoast();
  
  //rgb
  void setRGB(int r, int g, int b);
  void setColor(int color);  //use the color defines
  void setColorByHue(int hue);
  void fade(int fadedelay);
  
  boolean button1_is_pressed();
  boolean button2_is_pressed();

  int usPing_R();
  int usPing_L();
  
  void setServoConfiguration(int configuration);
  
  NewPing *sonar_L; // NewPing setup of pins and maximum distance.
  NewPing *sonar_R; // NewPing setup of pins and maximum distance.
  
  Servo Servo_A;
  Servo Servo_B;
  Servo Servo_C;
  
  //QTRSensorsRC qtrrc;
  //unsigned int sensorValues[2];  //variable for line sensors

private:

  //convert a hue (0-1023) to rgb colors
  void h2rgb(float H, int& R, int& G, int& B);

  uint8_t _button1;
  uint8_t _button2; 
  
  //motor speeds
  uint8_t _mot1Speed; 
  uint8_t _mot2Speed;
  
  uint8_t _turnSpeed0;
  int _turnDelay; 
  
  //thresholds
  int _lineThreshold;
  int _pingThreshold;
  
  //tempo
  int _tempo;
  float _fTemp;
  
  //servo_config
  // 0 both motors fwd
  // 1 B fwd, C rev
  // 2 B rev, C fwd
  // 3 both backwards
  int _servo_configuration; // 0..3  both forward, etc.
  boolean _BForward;
  boolean _CForward;
};


#endif


