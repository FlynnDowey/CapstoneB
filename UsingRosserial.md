# How to get ROS working on an arduino

## Introduction

This document provides instructions for connecting ros with arduino code

## Prerequisites

- ROS installed
- rosserial library 

## Code Execution

Follow these steps:

1. Compile and upload your code to the arduino using the following command
```
./arduino_cli_upload.sh sketchbook/my_sketch/
```
Note: if you are using the arduino leonardo you must insert `#define USE_USBCON` BEFORE `#include <ros.h>`.
2. Run the following command after the code has been uplaoded.  
```
rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0
```
