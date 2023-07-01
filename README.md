# CapstoneB: tutorials

[Creating ROS workspace](CreatingROSWorkspace.md)

[Multiple machines in ROS](MultipleMachines.md)

[How to use rosserial](UsingRosserial.md)

[Using an arduino-cli](CompilingAndUploadingArduino.md)

Remaining items to complete:
1. Figure out how to use Rtabmap with navigation stack (move_base).
2. Adjust parameters in move_base, [here](meeting/src/robot_navigation/param)
3. Implement and test on the robot.
4. Add IMU + ROS drivers
5. Add ultrasound to [costmap](meeting/src/robot_navigation/param/costmap_common_params.yaml) 
6. Wifi stuff ad power??

You need to download turtlebot3 to use the simulation, it can be downloaded using
```
sudo apt-get install ros-noetic-turtlebot3 (tab tab tab)
```
To run the navigation stack, simply run:
```
roslaunch robot_navigation healthbot_navigation localization:=true
```
