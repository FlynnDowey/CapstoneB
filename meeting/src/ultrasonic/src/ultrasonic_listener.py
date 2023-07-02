#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Range
import serial

rospy.init_node('ultrasonic_listener')

# Serial communication settings
serial_port = '/dev/ttyACM0'  # Update with the correct serial port
baud_rate = 115200

# Create a publisher for the /cmd_vel topic
pub_l = rospy.Publisher('/ultrasonic_l', Range, queue_size=10)
pub_r = rospy.Publisher('/ultrasonic_r', Range, queue_size=10)
pub_b = rospy.Publisher('/ultrasonic_b', Range, queue_size=10)

# Open the serial port for communication with Arduino
ser = serial.Serial(serial_port, baud_rate)

# Initialize Range messages
range_l_msg = Range()
range_r_msg = Range()
range_b_msg = Range()

# Set common fields for Range messages
header = rospy.Header()
header.frame_id = 'ultrasonic_sensor'

range_min = 0.2  # Replace with the minimum range value of your ultrasonic sensor
range_max = 4.0  # Replace with the maximum range value of your ultrasonic sensor

range_l_msg.radiation_type = Range.ULTRASOUND
range_l_msg.field_of_view = 0.1  # Replace with the field of view of your ultrasonic sensor
range_l_msg.min_range = range_min
range_l_msg.max_range = range_max
range_l_msg.header = header

range_r_msg.radiation_type = Range.ULTRASOUND
range_r_msg.field_of_view = 0.1  # Replace with the field of view of your ultrasonic sensor
range_r_msg.min_range = range_min
range_r_msg.max_range = range_max
range_r_msg.header = header

range_b_msg.radiation_type = Range.ULTRASOUND
range_b_msg.field_of_view = 0.1  # Replace with the field of view of your ultrasonic sensor
range_b_msg.min_range = range_min
range_b_msg.max_range = range_max
range_b_msg.header = header

# Read and process serial data
while not rospy.is_shutdown():
    if ser.in_waiting > 0:
        line = ser.readline().decode().strip()
        distances = line.split(',')

        if len(distances) == 3:
            # Update Range messages with new measurements
            range_l_msg.range = float(distances[0])
            range_r_msg.range = float(distances[1])
            range_b_msg.range = float(distances[2])

            # Publish Range messages
            pub_l.publish(range_l_msg)
            pub_r.publish(range_r_msg)
            pub_b.publish(range_b_msg)
    rospy.sleep(0.1)

ser.close()
