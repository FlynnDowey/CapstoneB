# Setting up the Kinect v2 with linux and ROS

## Introduction

This document provides instructions for getting the kinect working on a linux.

## Prerequisites

- A distro of ROS installed

## Code Execution

1. Download ``libfreeconect2`` from [https://github.com/OpenKinect/libfreenect2.git](https://github.com/OpenKinect/libfreenect2.git) and build the library. 
```
git clone https://github.com/OpenKinect/libfreenect2.git
cd 
```
2. 
```
source devel/setup.bash
```
3. Ensure ROS_PACKAGE_PATH has your working directory
```
echo $ROS_PACKAGE_PATH
```
