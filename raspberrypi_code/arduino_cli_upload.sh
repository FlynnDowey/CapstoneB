#!/bin/bash

# Step 1: Verify the sketch name argument
if [ $# -eq 0 ]; then
    echo "No sketch name provided. Please provide the sketch name as an argument."
    exit 1
fi

sketch_name="$1"

# Step 2: Compile the sketch
arduino-cli compile --fqbn arduino:avr:megaADK "$sketch_name"

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Step 3: Upload the sketch
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:megaADK "$sketch_name"

if [ $? -ne 0 ]; then
    echo "Upload failed."
    exit 1
fi

# Step 4: Done!
echo "Sketch compilation and upload complete."

