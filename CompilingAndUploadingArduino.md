# Compiling and Uploading to Arduino

## Introduction

This document provides instructions for uploading and compiling sketches in linux to arduino.

## Prerequisites

Before getting started, ensure that you have the following:

- arduino-cli

## Installation

Follow the installation instructions found here: https://arduino.github.io/arduino-cli/0.32/installation/ and set up the arduino enviroment 
from this link: https://arduino.github.io/arduino-cli/0.32/getting-started/

## Uploading and Compiling Sketches

You can either use the uploaded bash script or use the following commmands:

1. compile the sketch
```
arduino-cli compile --fqbn arduino:avr:leonardo MySketch
```
2. upload the sketch
```
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo MySketch
```
