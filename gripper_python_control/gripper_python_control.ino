/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

// servos for right and left grippers
Servo r_servo;  
Servo l_servo;  

// Home positions
const int r_home = 180;  
const int l_home = 0;  

// set gripper opening limit
const int max_angle = 45;

// go to gripper home position
void close_fully();

// set angle for both gripper arms at once
void set_angle(int angle);

void setup() {
  // start serial communication
  Serial.begin(115200);

  // attaches the servos [r_servo-> D9, l_servo->D6]
  r_servo.attach(9);  
  l_servo.attach(6);  

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // start in fully closed position
  close_fully();
}

void loop() {

  while (!Serial.available());{

  // read character from serial port
   int x = Serial.readString().toInt();

// closing
 if(x==1){
    set_angle(8);

    // turn on led indicatpr 
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.println("Closing...");
 }

// opening
else if(x==0){
  
  set_angle(30);
  Serial.println("Opening...");

  // turn on led indicator 
    digitalWrite(LED_BUILTIN, LOW);
}

  }
}


void set_angle(int angle){

  if(angle <= max_angle ){
  l_servo.write(angle); 
  r_servo.write(180 - angle); 
  }
}

void close_fully(){
  set_angle(0);
}

void open_fully(){
  set_angle(max_angle); 
}
