#!/bin/bash
WORKSPACE=/home/ubuntu/dev/buddy_bot_ros

source /opt/ros/jazzy/setup.bash
source $WORKSPACE/install/setup.bash
ros2 run motor_control motor_controller