#!/bin/sh
#Not the best approach to use $pwd as it breaks with change in folder structure.
#Best practice is to add the source path to ~/.bashrc and source that once.
xterm -e "source $(pwd)/../../devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../map/UdacityProject1.world " &
sleep 5
xterm -e "source $(pwd)/../../devel/setup.bash;roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../map/map.yaml" &
sleep 5
xterm -e "source $(pwd)/../../devel/setup.bash;roslaunch my_robot navigation_markers_rviz.launch" &
sleep 
xterm -e "source $(pwd)/../../devel/setup.bash;rosrun add_markers add_markers" &
sleep 5
xterm -e "source $(pwd)/../../devel/setup.bash;rosrun pick_objects pick_objects"
