#!/bin/sh
xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_house.launch" &
sleep 2
xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch" & 
sleep 1
# xterm  -e  " roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" &
# sleep 1
xterm  -e  " rosrun udemy_ros_beginners move_stop_turtlebot3_cpp"