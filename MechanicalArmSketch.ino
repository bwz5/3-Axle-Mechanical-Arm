#include <Servo.h>
 
Servo smallArmZ;  // the second arm of the robot

Servo baseArmZ;  // the arm attached to the base of the robot

Servo baseX;  // the base stand of the robot that controls turns in the xy plane
 
int pos = 0;    // variable to store the servo position

const int trigPinLeft = 6;  // stores trig pin for hc sr04 
const int echoPinLeft = 5; // stores echo pin for hc sr04

const int trigPinRight = 3; 
const int echoPinRight = 2; 

float durationLeft, distanceLeft; 

float durationRight, distanceRight; 

void setup() {
  smallArmZ.attach(9);  // attaches the servos 
  baseArmZ.attach(10); 
  baseX.attach(11); 

  pinMode(trigPinLeft, OUTPUT); // eastablishes the hc sr04 with their respective pins 
  pinMode(echoPinLeft, INPUT); 

  pinMode(trigPinRight, OUTPUT); 
  pinMode(echoPinRight, INPUT); 

  Serial.begin(9600); 
}

int distanceMeasure(int trigPin, int echoPin){ // uses the hc sr04 to measure the distance to a target in front of it via ultrasound
  digitalWrite(trigPin, LOW);  

	delayMicroseconds(2);  

	digitalWrite(trigPin, HIGH);  

	delayMicroseconds(10);  

	digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH);

  return  (duration *.0343)/2;  
}

void turn180(Servo s){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    s.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }

    for (pos = 180; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    s.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }

    
}

void turn90(Servo s){
  for (pos = 180; pos >= 75; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    s.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }

  for (pos = 75; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    s.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }
}
 
void loop() {
  // Left distance sensor
  distanceLeft = distanceMeasure(trigPinLeft, echoPinLeft);  
  Serial.println(distanceLeft);   

  // Right distance sensor 
  distanceRight = distanceMeasure(trigPinRight, echoPinRight); 
  Serial.println(distanceRight); 

  if (distanceLeft < 5.0){
    turn180(baseX); 
  }
  if (distanceRight < 5.0){
    turn90(baseArmZ); 
    turn180(smallArmZ);
  }
  delay(100); 

}