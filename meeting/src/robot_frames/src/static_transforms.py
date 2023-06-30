#!/usr/bin/env python
import rospy
import tf
from tf.transformations import quaternion_from_euler

def make_transform(pose):
    translation = (pose[0], pose[1], pose[2])
    rotation = quaternion_from_euler(pose[3], pose[4], pose[5])
    return translation, rotation

if __name__ == "__main__":
    rospy.init_node("static_transforms")

    broadcaster = tf.TransformBroadcaster()

    rate = rospy.Rate(10.0) # 10Hz
    while not rospy.is_shutdown():
        current_time = rospy.Time.now()
        # base_link -> base_footprint
        broadcaster.sendTransform(*make_transform([0, 0, 0.024, 0, 0, 0]), current_time, "base_link", "base_footprint")
        # front_left -> base_link
        broadcaster.sendTransform(*make_transform([0.168, 0.2028, 0.024, 0, 0, 0]), current_time, "front_left", "base_link")
        # front_right -> base_link
        broadcaster.sendTransform(*make_transform([0.168, -0.2028, 0.024, 0, 0, 0]), current_time, "front_right", "base_link")
        # rear_left -> base_link
        broadcaster.sendTransform(*make_transform([-0.168, 0.2028, 0.024, 0, 0, 0]), current_time, "rear_left", "base_link")
        # rear_right -> base_link
        broadcaster.sendTransform(*make_transform([-0.168, -0.2028, 0.024, 0, 0, 0]), current_time, "rear_right", "base_link")
        # front_bumper -> base_link
        broadcaster.sendTransform(*make_transform([0.216, 0, 0.024, 0, 0, 0]), current_time, "front_bumper", "base_link")
        # rear_bumper -> base_link
        broadcaster.sendTransform(*make_transform([-0.216, 0, 0.024, 0, 0, 0]), current_time, "rear_bumper", "base_link")
        # kinect_frame -> base_link
        broadcaster.sendTransform(*make_transform([0, 0, 0.024, 0, 0, 0]), current_time, "laser_frame", "base_link")

        # ultrasonic_l_frame -> base FIX THE POSE
        broadcaster.sendTransform(*make_transform([0, 0.2000, 0.024, 0, 0, 1.5708]), current_time, "ultrasonic_l_frame", "base_link")
        # ultrasonic_r_frame -> base FIX THE POSE
        broadcaster.sendTransform(*make_transform([0, -0.2000, 0.024, 0, 0, 4.7124]), current_time, "ultrasonic_r_frame", "base_link")
        # ultrasonic_b_frame -> base FIX THE POSE
        broadcaster.sendTransform(*make_transform([-0.216, 0, 0.024, 0, 0, 3.1416]), current_time, "ultrasonic_b_frame", "base_link")
        rate.sleep()
