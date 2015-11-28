#include "MIYbot.h"
#include <QTRSensors.h>
#include <NewPing.h>
#include <TimerFreeTone.h>
#include <Servo.h> 
#include <stdio.h>

void MIYbot::setup(){
  
  //set up the user switches...
  pinMode(SW_1, INPUT);    // declare pushbutton as input
  //digitalWrite(SW_1,HIGH);  //engages internal pullup resistor
  pinMode(SW_2, INPUT);    // declare pushbutton as input
  //digitalWrite(SW_2,HIGH);  //engages internal pullup resistor
  
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT);  
  pinMode(LED_B, OUTPUT);  

  pinMode(BUZZER, OUTPUT);
  
  pinMode(LINE_SENSOR_LEFT, INPUT);
  pinMode(LINE_SENSOR_RIGHT, INPUT);
  
  pinMode(L_TRIGGER_PIN, INPUT);
  pinMode(L_ECHO_PIN, INPUT);
  pinMode(R_TRIGGER_PIN, INPUT);
  pinMode(R_ECHO_PIN, INPUT);
       
  Servo_A.attach(SERVO_A);
  Servo_A.write(90); 
  Servo_B.attach(SERVO_B);
  Servo_A.write(90); 
  Servo_C.attach(SERVO_C);
  Servo_A.write(90); 

  //===========================================================================//
  // initialize the line and ultrasonic sensors
  //initialize the line sensors
  //QTRSensorsRC qtrrc((unsigned char[]) {LINE_SENSOR_LEFT, LINE_SENSOR_RIGHT},  2, 2048, QTR_NO_EMITTER_PIN); 
  
  //initialize the ultrasonic
  sonar_L = new NewPing(L_TRIGGER_PIN, L_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
  sonar_R = new NewPing(R_TRIGGER_PIN, R_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
}

void MIYbot::setMotorSpeed(uint8_t speed){
}

  
//buzzer functions
void MIYbot::beep(){
  TimerFreeTone(BUZZER, NOTE_C7, 350);
  //noNewTone;
  delay(100);
}

void MIYbot::playNote(int note, int note_len){
  //note_len should be:
  //  1  Whole note
  //  2  half note
  //  4  quarter note
  //  8  eighth note
  //  16 sixteenth note
  //  These times relate to the tempo (beats per minute) that is set.
  _fTemp = (100000/_tempo)*(4/note_len);
  Serial.println((int)_fTemp);
  TimerFreeTone(BUZZER, note, (int)_fTemp);
}

void MIYbot::rest(int note_len){
  //note_len should be:
  //  1  Whole note
  //  2  half note
  //  4  quarter note
  //  8  eighth note
  //  16 sixteenth note
  //  These times relate to the tempo (beats per minute) that is set.
  //noNewTone();
  _fTemp = (100000/_tempo)*(4/note_len);
  delay((int)_fTemp);
}  

void MIYbot::setTempo(int tempo) {
  //a good value here would be a tempo of 100 or 100 beats/minute
  //this program uses 4/4 so a whole note is 4 beats, a half note is 2 and so on....
 _tempo = tempo; 
}


void MIYbot::MotorRun(int servo, int pwm_speed, boolean reverse){
  if (pwm_speed > SUPER_FAST) pwm_speed = SUPER_FAST; //put on a governer!
  if(reverse){ 
    if (servo == 1) Servo_A.write(90 - pwm_speed);
    else if (servo == 2) {
      if (_BForward) Servo_B.write(90 - pwm_speed);
      else Servo_B.write(90 + pwm_speed);
    }
    else if (servo == 3) {
      if (_CForward) Servo_C.write(90 - pwm_speed);
      else Servo_C.write(90 + pwm_speed);
    }
  } else {
    if (servo == 1) Servo_A.write(90 + pwm_speed);
    else if (servo == 2) {
      if (_BForward) Servo_B.write(90 + pwm_speed);
      else Servo_B.write(90 - pwm_speed);
    }
    else if (servo == 3) {
      if (_CForward) Servo_C.write(90 + pwm_speed);
      else Servo_C.write(90 - pwm_speed);
    }
  }
}  
         
//movement
void MIYbot::forward(int pwm_speed){
  MotorRun(2,pwm_speed,true);
  MotorRun(3,pwm_speed,true);
}

void MIYbot::reverse(int pwm_speed){
  MotorRun(2,pwm_speed,false);
  MotorRun(3,pwm_speed,false);
}

void MIYbot::spin(int duration, boolean reverse){
  MotorRun(2,SLOW,reverse);
  MotorRun(3,SLOW,! reverse);
  delay(duration);
  motorStop();
}

void MIYbot::motorStop(){
  MotorRun(2,0,true);
  MotorRun(3,0,true);
}

void MIYbot::motorCoast(){
 //         digitalWrite(MOT_EN1,LOW); //set pwm control, 0 for stop, and 255 for maximum speed
//          digitalWrite(MOT_EN2,LOW); //set pwm control, 0 for stop, and 255 for maximum speed
}


//rgb
void MIYbot::setRGB(int r, int g, int b){
    analogWrite(LED_G, g);
    analogWrite(LED_B, b);
    analogWrite(LED_R, r);
}


// hue is between 0 and 1024
void MIYbot::setColor(int color){
  
    setRGB(0, 0, 0);  //off
    delay(200);
    
    switch (color) {
      case OFF:
        setRGB(0, 0, 0);  //off
        break;
      case YELLOW:
        setRGB(250, 200, 0);   // Yellow
        break;
      case ORANGE:
        setRGB(255, 40, 0);    // Orange
        break;
      case RED:
        setRGB(255, 0, 0);     // Red
        break;
      case BLUE:
        setRGB(10, 10, 255);   // Blue
        break;
      case PINK:
        setRGB(255, 0, 100);   // Pink
        break;
      case PURPLE:
        setRGB(200, 0, 255);   // Purple
        break;
      case GREEN:
        setRGB(0, 255, 0);     // Green
        break;
      case WHITE:
        setRGB(255, 255, 255); // White
        break;
      case DIMWHITE:
        setRGB(10, 10, 10); // White
        break;  
      case AQUA:
        setRGB(0, 255, 255); // White
        break;  
      default: 
        setRGB(0, 0, 0);  //off
        break;
     }
}

// hue is between 0 and 1024
void MIYbot::setColorByHue(int hue){
    int r;
    int g;
    int b;
    float h = ((float)hue)/1024;
    h2rgb(h, r, g, b);
    setRGB( r,  g,  b);
    Serial.print (h) ;
    Serial.print ("  ") ;
    Serial.print (r) ;
    Serial.print ("  ") ;
    Serial.print (g) ;
    Serial.print ("  ") ;
    Serial.print (b) ;
    Serial.println ("  ") ;

}

void MIYbot::fade(int fade_delay){
    int i;

    //run through a color loop
    for (i=0; i<=1023; i++) {
      setColor(i);
      delay(fade_delay);
  }
  //lights off!
  //setRGB(0,0,0);
}

boolean MIYbot::button1_is_pressed(){
     int button1;
     button1 = digitalRead(SW_1);  // read input value
    
     if (button1 == HIGH ) { //it is pushed
       delay(400);
       button1 = digitalRead(SW_1);  // read input value
       if (button1 == LOW ) { //it is pushed
           return true;
       }
     } 
     else {
        return false;
     }
}

boolean MIYbot::button2_is_pressed(){
     int button2;
     button2 = digitalRead(SW_2);  // read input value
    
     if (button2 == HIGH ) { //it is pushed
       delay(400);
       button2 = digitalRead(SW_2);  // read input value
       if (button2 == LOW ) { //it is pushed
           return true;
       }
     } 
     else {
        return false;
     }
}


//convert a hue (0-1023) to rgb colors
//This code comes from...
//http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1207331496

void MIYbot::h2rgb(float H, int& R, int& G, int& B) {

  int var_i;
  float S=1, V=1, var_1, var_2, var_3, var_h, var_r, var_g, var_b;

  if ( S == 0 )                       //HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      //H must be < 1
    var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if      ( var_i == 0 ) {
      var_r = V     ;
      var_g = var_3 ;
      var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
      var_r = var_2 ;
      var_g = V     ;
      var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
      var_r = var_1 ;
      var_g = V     ;
      var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
      var_r = var_1 ;
      var_g = var_2 ;
      var_b = V     ;
    }
    else if ( var_i == 4 ) {
      var_r = var_3 ;
      var_g = var_1 ;
      var_b = V     ;
    }
    else                   {
      var_r = V     ;
      var_g = var_1 ;
      var_b = var_2 ;
    }

    R = (1-var_r) * 255;                  //RGB results = 0 ÷ 255
    G = (1-var_g) * 255;
    B = (1-var_b) * 255;
  }
}


//ultrasonic ping
int MIYbot::usPing_R(){
  return sonar_R->ping(); // Send ping, get ping time in microseconds (uS).
}

int MIYbot::usPing_L(){
  return sonar_L->ping(); // Send ping, get ping time in microseconds (uS).
}

void MIYbot::setServoConfiguration(int configuration){
  _servo_configuration = configuration;
  if (configuration == 0) {
    _BForward = true;
    _CForward = true;
  } else if (configuration == 1) {
    _BForward = true;
    _CForward = false; 
  } else if (configuration == 2) {
    _BForward = false;
    _CForward = true; 
  } else if (configuration == 3) {
    _BForward = false;
    _CForward = false; 
  }
}


/*        
//===========================================================================//     

void Countdown_1(){
  int i = 1;
  //count down 5 seconds
  while (i <= 5) {
    RGBLed(255, 0, 0);
    TimerFreeTone(Buzzer_Servo, 784, 50); 
    delay(450);
    RGBLed(0, 0, 0);
    delay(500);
    i++;
  }
}

void Countdown_2(){
  int i = 1;
  //count down 5 seconds
  while (i <= 5) {
    RGBLed(0, 255, 0);
    TimerFreeTone(Buzzer_Servo, 392, 50); 
    delay(450);
    RGBLed(0, 0, 0);
    delay(500);
    i++;
  }
}
*/
