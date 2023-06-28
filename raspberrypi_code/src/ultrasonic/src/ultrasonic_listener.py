#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
import serial

class ObstacleAvoidanceNode:
    def __init__(self):
        rospy.init_node('ultrasonic_listener')

        # Serial communication settings
        self.serial_port = '/dev/ttyACM0'  # Update with the correct serial port
        self.baud_rate = 115200

        # Obstacle detection threshold
        self.distance_threshold = 20  # Threshold distance for obstacle detection in cm

        # Velocity commands for slowing down the robot
        self.linear_velocity = 0.2  # Adjust as needed
        self.angular_velocity = 0.1  # Adjust as needed
        
        # Create a publisher for the /cmd_vel topic
        self.cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)

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
                line = ser.readline().decode().strip()
                distances = line.split(',')

                if len(distances) == 3:
                    try:
                        left_distance = float(distances[0])
                        right_distance = float(distances[1])
                        back_distance = float(distances[2])

                        # Check if obstacle is too close
                        if (
                            left_distance <= self.distance_threshold
                            or right_distance <= self.distance_threshold
                            or back_distance <= self.distance_threshold
                        ):
                            #rospy.logwarn("Obstacle detected! Changing robot speed.")

                            # Create a modified Twist message to slow down the robot
                            modified_twist = Twist()
                            modified_twist.linear.x = self.linear_velocity
                            modified_twist.angular.z = self.angular_velocity

                            # Publish the modified Twist message to the /cmd_vel topic
                            self.cmd_vel_pub.publish(modified_twist)
                    
                    except ValueError:
                        rospy.logerr("Error parsing distance values: %s", line)
                else:
                    rospy.logerr("Invalid number of distance values: %s", line)

if __name__ == '__main__':
    try:
        node = ObstacleAvoidanceNode()
        node.main()
    except rospy.ROSInterruptException:
        pass
