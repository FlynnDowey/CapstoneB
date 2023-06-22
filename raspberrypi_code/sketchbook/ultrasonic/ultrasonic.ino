#define USE_USBCON
#include <ros.h>  
#include <std_msgs/UInt64.h>  
ros::NodeHandle nh;  
std_msgs::UInt64 distanceros;  
ros::Publisher ultrasonic("ultrasonic", &distanceros);  
  
const int trigger = 9;  
const int echo = 10;  
 
// defines variables  
long duration;  
int dist;  

void setup() { 
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(trigger, OUTPUT); // Sets the trigPin as an Output  
  pinMode(echo, INPUT); // Sets the echoPin as an Input  
  Serial.begiYou need to configure the serial communication between the Arduino and Raspberry Pi properly, ensuring that the messages are transmitted and received correctly.n(9600); // Starts the serial communication  
  nh.initNode();  
  nh.advertise(ultrasonic);  
}  
 
void loop() {   
// Clears the trigPin  
  digitalWrite(trigger, LOW);  
  delayMicroseconds(2);    

// Sets the trigPin on HIGH state for 10 micro seconds  
  digitalWrite(trigger, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigger, LOW);  

// returns the sound wave travel time in microseconds  
  duration = pulseIn(echo, HIGH);//works on pulses from 10 microseconds to 3 minutes in length  

// Getting the distance  
  dist = duration*0.034/2;  

  distanceros.data = dist;  
  ultrasonic.publish(&distanceros);  
  nh.spinOnce();  
  delay(1);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);  
}  
