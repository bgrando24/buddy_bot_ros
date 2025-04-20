# Buddy Bot - ROS Version!

This repo migrates the v1 of buddy_bot over to using ROS 2 (Jazzy).


## Typical workflow for dev/build


1. Edit source file
2. Build updated package ```colcon build --symlink-install```
3. Source updated environment ```source install/setup.bash```
4. Run node	```ros2 run [pkg] [module]```