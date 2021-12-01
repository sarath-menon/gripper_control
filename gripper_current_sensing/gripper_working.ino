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

// status flags
bool starting = false;
bool object_detected = false;
bool maintaining = false;

// above this, consodered as object_detected
const int threshold = 1;

// set gripper opening limit
const int max_angle = 45;

// gripper starting angle 
const int start_angle = 30;

// 
int angle_cmd = 0;
int maintain_cmd = 0;

// count number of time object detected fo robust checking
int object_count = 0;
int prev_object_count = 0;

// go to gripper home position
void close_fully();

// set angle for both gripper arms at once
void set_angle(int angle);

// check if object has been object_detected
bool check_object_detected();

// read current gripper angle
int get_gripper_angle();

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // use analog pin 1 for voltage measurement
  pinMode(A1, INPUT);

 // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // attaches the servos [r_servo-> D9, l_servo->D6]
  r_servo.attach(9);  
  l_servo.attach(6);  

  // set gripper to open position
  open_fully();
}

void loop() {

    // get current gripper position
    int current_angle = get_gripper_angle();
        Serial.print("Current angle:");
    Serial.println(current_angle);


    // check if object detect
    object_detected = check_object_detected();

    if(object_detected){    // increment counter
      object_count++;
      }
//
//    Serial.print("Detection count:");
//    Serial.println(object_count);
   
    // if object_detected, stop closing [object count for robust checking]
    if(object_count >2){
      set_angle(angle_cmd);
      Serial.println("Object detected for real");
    }
    
    // if no grasp detected till closing, open fully and try again
    else if (current_angle==0){
      
    open_fully();
    delay(1000);
    Serial.println("Resetting");
    }

    // else, continue closing
    else{
    // if reached here, means false detection for object detecting
    if(prev_object_count == object_count){
    object_count= 0;}

    // control algorithm here
    angle_cmd = current_angle-1;

    delay(200);

    set_angle(angle_cmd);
    }

//    Serial.print("Angle command:");
//    Serial.println(angle_cmd);

  
  prev_object_count = object_count;
}


void set_angle(int angle){

  if(angle <= max_angle ){
  l_servo.write(angle); 
  r_servo.write(180 - angle); 
  }

  else{Serial.println("Invalid angle: Beyond max limit");}
}

void close_fully(){
  set_angle(0);
}

void open_fully(){
  set_angle(start_angle); 
}

bool check_object_detected(){

  // reading voltag
  int servo_volt = analogRead(A1);
  Serial.print("Servo volt: ");
  Serial.println(servo_volt);
  


  // print sensor value to serial monitor
  if(servo_volt > threshold){
    Serial.println("Object detected");
    return true;
  }
  
  else{
//    Serial.println("No object");
    return false;
  }
}

int get_gripper_angle(){

  return l_servo.read(); 
}


//     // check if starting
//    if(abs(current_angle - start_angle) < 10){object_detected = false;}
//    
  
