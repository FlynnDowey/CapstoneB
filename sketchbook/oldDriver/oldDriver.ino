#include <ros.h>
#include <ros/time.h>
#include "Arduino.h"
#include "PinChangeInterrupt.h"
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "PID_v2.h"
#include <tf/tf.h>
#include <std_msgs/Int32.h>
// --------------- For ROS ---------------------
ros::NodeHandle nh;

std_msgs::Int32 encoder0_msg;
std_msgs::Int32 encoder1_msg;
std_msgs::Int32 encoder2_msg;
std_msgs::Int32 encoder3_msg;
ros::Publisher encoder0_pub("encoder0", &encoder0_msg);
ros::Publisher encoder1_pub("encoder1", &encoder1_msg);
ros::Publisher encoder2_pub("encoder2", &encoder2_msg);
ros::Publisher encoder3_pub("encoder3", &encoder3_msg);


double wheel1_velocity = 0;
double wheel2_velocity = 0;
double wheel3_velocity = 0;
double wheel4_velocity = 0;

double R = 0.048;
double l1 = 0.220 + 0.0185;
double l2 = 0.120;
double L = l1 + l2;

double x = 0.0;
double y = 0.0;
double th = 0.0;


void cmd_vel_callback(const geometry_msgs::Twist& msg) {
  double linear_x = (double)msg.linear.x;
  double linear_y = (double)msg.linear.y;
  double angular_z = (double)msg.angular.z;

  // Calculate wheel velocities... no idea if this is correct
  wheel1_velocity = (1 / R) * (linear_x - linear_y + (L * angular_z));
  wheel2_velocity = (1 / R) * (linear_x + linear_y + (L * angular_z));
  wheel3_velocity = (1 / R) * (linear_x + linear_y - (L * angular_z));
  wheel4_velocity = (1 / R) * (linear_x - linear_y - (L * angular_z));

}

ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("cmd_vel", &cmd_vel_callback);

double Pk1 = 4;
double Ik1 = 4;
double Dk1 = 0.03;

double Setpoint1, Input1;
double Output1; // PID variables PID PIDI (Input1, Output1, Setpoint1, Pki, Iki, Dk1, DIRECT);
PID PID1 (&Input1, &Output1, &Setpoint1, Pk1, Ik1, Dk1, DIRECT); // PID Setup
// PID Setup

double Pk2 = 4;
double Ik2 = 4;
double Dk2 = 0.03;

double Setpoint2, Input2;
double Output2; // PID variables
PID PID2 (&Input2, &Output2, &Setpoint2, Pk2, Ik2, Dk2, DIRECT); // PID Setup

double Pk3 = 4;
double Ik3 = 4;
double Dk3 = 0.03;

double Setpoint3, Input3;
double Output3; // PID variables PID PIDI (Input1, Output1, Setpoint1, Pki, Iki, Dk1, DIRECT);
PID PID3 (&Input3, &Output3, &Setpoint3, Pk3, Ik3, Dk3, DIRECT); // PID Setup
// PID Setup

double Pk4 = 4;
double Ik4 = 4;
double Dk4 = 0.03;

double Setpoint4, Input4;
double Output4; // FID variables
PID PID4 (&Input4, &Output4, &Setpoint4, Pk4, Ik4, Dk4, DIRECT); // PID Setup

unsigned long currentMillis;
unsigned long previousMillis;

volatile float desiredVel1;
volatile float desiredVel2;
volatile float desiredVel3;
volatile float desiredVel4;

//encoder interrupts
//front encoders
#define encoder0PinA 2  //encoder 0
#define encoder0PinB 3

#define encoder1PinA 20  //encoder 1
#define encoder1PinB 21

//back encoders
#define encoder2PinA 18  //encoder 2
#define encoder2PinB 19

#define encoder3PinA 50  //encoder 3
#define encoder3PinB 52

#define CPR 1440
#define sampleT 10

volatile long encoder0Pos = 0;
volatile long encoder1Pos = 0;
volatile long encoder2Pos = 0;
volatile long encoder3Pos = 0;

float encoder0Diff;
float encoder1Diff;
float encoder2Diff;
float encoder3Diff;

float encoder0Prev;
float encoder1Prev;
float encoder2Prev;
float encoder3Prev;

float encoder0Error;
float encoder1Error;
float encoder2Error;
float encoder3Error;

void setup() {

  nh.initNode();
  nh.subscribe(cmd_vel_sub);
  nh.advertise(encoder0_pub);
  nh.advertise(encoder1_pub);
  nh.advertise(encoder2_pub);
  nh.advertise(encoder3_pub);

  pinMode(5, OUTPUT); //front   motors
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT); //back motors
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(encoder1PinA, INPUT_PULLUP);
  pinMode(encoder1PinB, INPUT_PULLUP);
  pinMode(encoder2PinA, INPUT_PULLUP);
  pinMode(encoder2PinB, INPUT_PULLUP);
  pinMode(encoder3PinA, INPUT_PULLUP);
  pinMode(encoder3PinB, INPUT_PULLUP);

  attachInterrupt(0, updateEncoder0_A, CHANGE);
  attachInterrupt(1, updateEncoder0_B, CHANGE);
  attachInterrupt(2, updateEncoder1_A, CHANGE);
  attachInterrupt(3, updateEncoder1_B, CHANGE);
  attachInterrupt(4, updateEncoder2_A, CHANGE);
  attachInterrupt(5, updateEncoder2_B, CHANGE);
  attachPCINT(digitalPinToPCINT(50), updateEncoder3_A, CHANGE);
  attachPCINT(digitalPinToPCINT(52), updateEncoder3_B, CHANGE);

  PID1.SetMode(AUTOMATIC);
  PID1.SetOutputLimits (-240, 240);
  PID1.SetSampleTime (10);
  PID2.SetMode (AUTOMATIC);
  PID2.SetOutputLimits (-240, 240);
  PID2.SetSampleTime (10);
  PID3.SetMode(AUTOMATIC);
  PID3.SetOutputLimits (-240, 240);
  PID3.SetSampleTime (10);
  PID4.SetMode (AUTOMATIC);
  PID4.SetOutputLimits (-240, 240);
  PID4.SetSampleTime (10);
  set_Vel1(wheel1_velocity);
  set_Vel2(wheel2_velocity);
  set_Vel3(wheel3_velocity);
  set_Vel4(wheel4_velocity);
}

void loop() {

  currentMillis = millis();

  /*
            Front
          W1-------W2
           |       |
    Left   |   C   |   Right
           |       |
          W3-------W4
             Back
  */

  set_Vel1(wheel1_velocity * 10);
  set_Vel2(wheel2_velocity * 10);
  set_Vel3(wheel3_velocity * 10);
  set_Vel4(wheel4_velocity * 10);

//  double vx = 0.048 * (wheel1_velocity + wheel2_velocity + wheel3_velocity + wheel4_velocity) / 4.0;
//  double vy = 0.048 * (wheel1_velocity - wheel2_velocity - wheel3_velocity + wheel4_velocity) / 4.0;
//  double vth = 0.048 * (-wheel1_velocity + wheel2_velocity - wheel3_velocity + wheel4_velocity) / (4.0 * (l1 + l2));

//  unsigned long current_time, last_time;
//  current_time = millis();
//  double dt = (current_time - last_time) / 1000.0; // Convert milliseconds to seconds
//  last_time = current_time;
//  th += vth * dt; // where dt is the time difference between the current loop iteration and the previous one.
  //
//  double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
//  double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
//  double delta_th = vth * dt;
//
//  x += delta_x;
//  y += delta_y;
//  th += delta_th;

//  odom.linear.x = vx;
//  odom.linear.y = vy;
//  odom.linear.z = 0;
//
//  odom.angular.z = vth;
//
//  geometry_msgs::Quaternion odom_quat = tf::createQuaternionFromYaw(th);
//  odom.pose.pose.orientation = odom_quat;

//  geometry_msgs::TransformStamped odom_trans;
//  odom_trans.header.stamp = nh.now();
//  odom_trans.header.frame_id = "odom";
//  odom_trans.child_frame_id = "base_link";
//  odom_trans.transform.translation.x = x;
//  odom_trans.transform.translation.y = y;
//  odom_trans.transform.translation.z = 0.0;
//  odom_trans.transform.rotation = odom_quat;
//  odom_broadcaster.sendTransform(odom_trans);

  //  //set the position
//  odom.header.stamp = nh.now();
//  odom.pose.pose.position.x = x;
//  odom.pose.pose.position.y = y;
//  odom.pose.pose.position.z = 0.0;
//  odom.pose.pose.orientation = odom_quat;

  //  //set the velocity
//  odom.child_frame_id = "base_link";
//  odom.twist.twist.linear.x = vx;
//  odom.twist.twist.linear.y = vy;
//  odom.twist.twist.angular.z = vth;

//  odom_pub.publish(&odom);

  if (currentMillis - previousMillis >= 10) {
    previousMillis = currentMillis;

    encoder0Diff = encoder0Pos - encoder0Prev;
    encoder1Diff = encoder1Pos - encoder1Prev;
    encoder2Diff = encoder2Pos - encoder2Prev;
    encoder3Diff = encoder3Pos - encoder3Prev;

    Setpoint1 = desiredVel1;
    Setpoint2 = desiredVel2;
    Setpoint3 = desiredVel3;
    Setpoint4 = desiredVel4;

    encoder0Error = Setpoint1 - encoder0Diff;
    encoder1Error = Setpoint2 - encoder1Diff;
    encoder2Error = Setpoint3 - encoder2Diff;
    encoder3Error = Setpoint4 - encoder3Diff;

    encoder0Prev = encoder0Pos;
    encoder1Prev = encoder1Pos;
    encoder2Prev = encoder2Pos;
    encoder3Prev = encoder3Pos;

  
    Input1 = encoder0Diff;
    PID1.Compute();

    Input2 = encoder1Diff;
    PID2.Compute();

    Input3 = encoder2Diff;
    PID3.Compute();

    Input4 = encoder3Diff;
    PID4.Compute();

    if (Output1 > 12) {
      Output1 = abs(Output1);
      analogWrite(6, Output1);
      analogWrite(5, 0);
    }
    else if (Output1 < -12) {
      Output1 = abs(Output1);
      analogWrite(5, Output1);
      analogWrite(6, 0);
    }
    else {
      analogWrite(6, 0);
      analogWrite(5, 0);
    }

    if (Output2 > 12) {
      Output2 = abs(Output2);
      analogWrite(10, Output2);
      analogWrite(9, 0);
    }
    else if (Output2 < -12) {
      Output2 = abs(Output2);
      analogWrite(9, Output2);
      analogWrite(10, 0);
    }
    else {
      analogWrite(10, 0);
      analogWrite(9, 0);
    }

    if (Output3 < -12) {
      Output3 = abs(Output3);
      analogWrite(8, Output3);
      analogWrite(7, 0);
    }
    else if (Output3 > 12) {
      Output3 = abs(Output3);
      analogWrite(7, Output3);
      analogWrite(8, 0);
    }
    else {
      analogWrite(8, 0);
      analogWrite(7, 0);
    }

    if (Output4 < -12) {
      Output4 = abs(Output4);
      analogWrite(11, Output4);
      analogWrite(12, 0);
    }
    else if (Output4 > 12) {
      Output4 = abs(Output4);
      analogWrite(12, Output4);
      analogWrite(11, 0);
    }
    else {
      analogWrite(12, 0);
      analogWrite(11, 0);
    }


  }

  encoder0_msg.data = encoder0Pos;
  encoder1_msg.data = encoder1Pos;
  encoder2_msg.data = encoder2Pos;
  encoder3_msg.data = encoder3Pos;
  encoder0_pub.publish(&encoder0_msg);
  encoder1_pub.publish(&encoder1_msg);
  encoder2_pub.publish(&encoder2_msg);
  encoder3_pub.publish(&encoder3_msg);
  nh.spinOnce();
}

void updateEncoder0_A() {
  if (digitalRead(encoder0PinA) == HIGH) {

    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;
    }
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }

  else
  {
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;
    }
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
}

void updateEncoder0_B() {
  if (digitalRead(encoder0PinB) == HIGH) {

    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;
    }
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }


  else {
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;
    }
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
}

void updateEncoder1_A() {

  if (digitalRead(encoder1PinA) == HIGH) {
    //Serial.print("eri");

    if (digitalRead(encoder1PinB) == LOW) {
      encoder1Pos = encoder1Pos + 1;
    }
    else {
      encoder1Pos = encoder1Pos - 1;
    }
  }

  else {
    //Serial.print("zbi");
    if (digitalRead(encoder1PinB) == HIGH) {
      encoder1Pos = encoder1Pos + 1;
    }
    else {
      encoder1Pos = encoder1Pos - 1;
    }
  }
}

void updateEncoder1_B() {
  if (digitalRead(encoder1PinB) == HIGH) {

    if (digitalRead(encoder1PinA) == HIGH) {
      encoder1Pos = encoder1Pos + 1;
    }
    else {
      encoder1Pos = encoder1Pos - 1;
    }
  }

  else {
    if (digitalRead(encoder1PinA) == LOW) {
      encoder1Pos = encoder1Pos + 1;
    }
    else {
      encoder1Pos = encoder1Pos - 1;
    }
  }
}

void updateEncoder2_A() {
  if (digitalRead(encoder2PinA) == HIGH) {

    if (digitalRead(encoder2PinB) == LOW) {
      encoder2Pos = encoder2Pos + 1;
    }
    else {
      encoder2Pos = encoder2Pos - 1;
    }
  }

  else {
    if (digitalRead(encoder2PinB) == HIGH) {
      encoder2Pos = encoder2Pos + 1;
    }
    else {
      encoder2Pos = encoder2Pos - 1;
    }
  }
}

void updateEncoder2_B() {
  if (digitalRead(encoder2PinB) == HIGH) {

    if (digitalRead(encoder2PinA) == HIGH) {
      encoder2Pos = encoder2Pos + 1;
    }
    else {
      encoder2Pos = encoder2Pos - 1;
    }
  }

  else {
    if (digitalRead(encoder2PinA) == LOW) {
      encoder2Pos = encoder2Pos + 1;
    }
    else {
      encoder2Pos = encoder2Pos - 1;
    }
  }
}

void updateEncoder3_A() {
  if (digitalRead(encoder3PinA) == HIGH) {

    if (digitalRead(encoder3PinB) == LOW) {
      encoder3Pos = encoder3Pos + 1;
    }
    else {
      encoder3Pos = encoder3Pos - 1;
    }
  }

  else {
    if (digitalRead(encoder3PinB) == HIGH) {
      encoder3Pos = encoder3Pos + 1;
    }
    else {
      encoder3Pos = encoder3Pos - 1;
    }
  }
}

void updateEncoder3_B() {
  if (digitalRead(encoder3PinB) == HIGH) {

    if (digitalRead(encoder3PinA) == HIGH) {
      encoder3Pos = encoder3Pos + 1;
    }
    else {
      encoder3Pos = encoder3Pos - 1;
    }
  }

  else {
    if (digitalRead(encoder3PinA) == LOW) {
      encoder3Pos = encoder3Pos + 1;
    }
    else {
      encoder3Pos = encoder3Pos - 1;
    }
  }
}

void set_Vel1(float vel) {
  desiredVel1 = vel;
}

void set_Vel2(float vel) {
  desiredVel2 = vel;
}

void set_Vel3(float vel) {
  desiredVel3 = vel;
}

void set_Vel4(float vel) {
  desiredVel4 = vel;
}

long get_Vel1() {
  return encoder0Pos;
}

long get_Vel2() {
  return encoder1Pos;
}

long get_Vel3() {
  return encoder2Pos;
}

long get_Vel4() {
  return encoder3Pos;
}
