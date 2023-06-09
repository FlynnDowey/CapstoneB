# Odometry and TF/TF2

This should provide a simple overview on how to execute and become familiar with tf and odom in ROS.

## tf and ROS

Execute the following code for a command line approach to broadcast a tf transform.
```
rosrun tf static_transform_publisher x y z yaw pitch roll frame_id child_frame_id period
```
where

- ``x``, ``y``, ``z``: The translation values for the transform.
- ``yaw``, ``pitch``, ``roll``: The rotation values (in radians) for the transform.
- ``frame_id``: The parent frame ID.
- ``child_frame_id``: The child frame ID.
- ``period``: The period (in seconds) at which to broadcast the transform.

## Resources

1. ROS overview on tf [https://wiki.ros.org/tf](https://wiki.ros.org/tf)
2. ROS tutorial on tf [https://wiki.ros.org/tf/Tutorials](https://wiki.ros.org/tf/Tutorials) - I would advise to stick with python.

Don't worry about tf2, the old version should be good for our purposes. 

## Odometry and ROS

What needs to be done:

- publish encoder data as odom data.
- ensure the error between the odom and map is minimal. 
- find a way to speed up connection from arduino to ros; Steven looked into this and I will attach a [link]() to the code he gave me, it might be a good starting point. 
- 

## Resources
1. ROS wiki on odometry [https://wiki.ros.org/navigation/Tutorials/RobotSetup/Odom](https://wiki.ros.org/navigation/Tutorials/RobotSetup/Odom) - this is the code you need to work with.
2. An article online [https://automaticaddison.com/how-to-publish-wheel-odometry-information-over-ros/](https://automaticaddison.com/how-to-publish-wheel-odometry-information-over-ros/)

