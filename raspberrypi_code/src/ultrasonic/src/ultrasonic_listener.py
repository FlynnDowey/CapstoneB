#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Range
from geometry_msgs.msg import Twist
import serial

class ObstacleAvoidanceNode:
    def __init__(self):
        rospy.init_node('ultrasonic_listener')
        
        # Serial communication settings
        self.serial_port = '/dev/ttyACM0'  # Update with the correct serial port
        self.baud_rate = 9600

        # Ultrasonic sensor topic and message type
        self.ultrasonic_topic = 'ultrasonic'
        self.ultrasonic_msg_type = Range

        # Obstacle detection threshold
        self.distance_threshold = 0.5  # Adjust as needed

        # Velocity commands for slowing down the robot
        self.linear_velocity = 0.2  # Adjust as needed
        self.angular_velocity = 0.1  # Adjust as needed
        
        # Create a publisher for the /cmd_vel topic
        self.cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
        
        # Create a subscriber for the ultrasonic topic
        rospy.Subscriber(self.ultrasonic_topic, self.ultrasonic_msg_type, self.ultrasonic_callback)

    def ultrasonic_callback(self, data):
        distance = data.range

        if distance < self.distance_threshold:
            # Create a modified Twist message to slow down the robot
            modified_twist = Twist()
            modified_twist.linear.x = self.linear_velocity
            modified_twist.angular.z = self.angular_velocity

            # Publish the modified Twist message to the /cmd_vel topic
            self.cmd_vel_pub.publish(modified_twist)

    def start_node(self):
        rospy.spin()

    def main(self):
        # Open the serial port for communication with Arduino
        ser = serial.Serial(self.serial_port, self.baud_rate)

        # Start the ROS node
        self.start_node()

        # Read and process serial data
        while not rospy.is_shutdown():
            if ser.in_waiting > 0:
                data = ser.readline().decode().strip()
                # Process the received data as needed

if __name__ == '__main__':
    try:
        node = ObstacleAvoidanceNode()
        node.main()
    except rospy.ROSInterruptException:
        pass
