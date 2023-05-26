# Creating a ROS Workspace

## Introduction

This document provides instructions for creating a ros workspace.

## Prerequisites

Before getting started, ensure that you have the following:

- A distro of ROS installed

## Code Execution

Follow these steps:

1. Create a working directory
```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
catkin_make
```
2. Source the files
```
source devel/setup.bash
```
3. Ensure ROS_PACKAGE_PATH has your working directory
```
echo $ROS_PACKAGE_PATH
```
