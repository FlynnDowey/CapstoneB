## Introduction

TODO: fix the robot model urdf and ensure it functions in gazebo and rviz.


## How to start

Follow these steps:
~~
1. Download the original urdf model from OneDrive
2. Extract the downloaded model into your ros workspace (assume it is in 'catkin_ws/src') and remove the 'launch' and 'urdf' directories.
3. Move the existing urdf and launch files into the downloaded model from OneDrive.
4. Remove the old model directory.
5. return to '~/catkin_ws' and run 'catkin_make'.
6. To launch the model run 'roslaunch Robot_Base healthbot.launch'
7. You should see gazebo and rviz appear in new windows
8. Open a new terminal and run 'rosrun teleop_twist_keyboard teleop_twist_keyboard.py' this will load the controller. Press 'l' or 'j' and increase the speed by using 'q'; just make the robot spin for now.
9. Navigate to the rviz window and add the following topics: 'laser_scan', 'Robot_Model' and 'odom'.

Note: everytime you open a new terminal, you must run ``source devel/setup.bash`` OR insert the following code in bashrc by using the following command ``code ~/.bashrc`` and pasting ``source <directory>/devel/setup.bash``. Also anytime you make a change to any file, you must return to ``CapstoneB/tutorials`` and run ``catkin_make``.

1. Launch gazebo using
```
roslaunch Robot_Base gazebo.launch
```
If you encounter errors, try increasing your memory.
2. Run each one of the following commands in different terminals.
```
rosrun robot_odom robot_odom
rosrun robot_frames <spam tab until you get a .py file>
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```

## Requirements

1. You should fix the urdf file so that the model is physically correct.
2. ~~Once the urdf file is correct and no random motion is seen in gazebo, you now need to ensure that movement in the simulator (gazebo) is also seen in rviz.
3. ~~Finally, refer to the following cite to fix the laser and xbox kinect plugin [https://classic.gazebosim.org/tutorials?tut=ros_gzplugins](https://classic.gazebosim.org/tutorials?tut=ros_gzplugins). Use rviz; once accomplished you should see laser data and camera data of the simulator (gazebo) in rviz.~~
