# Connecting ROS between two machines

## Introduction

This document provides instructions for connecting ros between multiple machines.

## Prerequisites

- ROS installed
- Internet connection on the host and the raspberrypi
- Known ip addresses

## Code Execution

Follow these steps:

1. ssh into the raspberrypi:
```
ssh flynn@raspberrypi.local
```
2. Open .bashrc and insert the following code (this is where roscore is going to run)
```
export ROS_MASTER_URI=http://192.168.1.1:11311
export ROS_IP=192.168.1.1 # raspberry pi ip address
```
Source the bashrc file.

3. On the host open bashrc and insert the following code
```
export ROS_MASTER_URI=http://192.168.1.1:11311 #roscore address 
export ROS_IP=192.168.1.2 #host machine IP address 
```
Source the bashrc file.

4. Run roscore on the raspberry pi and run the following code in a new terminal.
```
rosrun rospy_tutorials listener.py
```
5. Run the following code, if no errors are present then it works!
```
rosrun rospy_tutorials talker.py
```
