/*
Devnath Nair
Udacity Robotics ND Program
Project 5 : Home Service Robot
*/

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
  ros::init(argc, argv, "pick_objects");
  
  MoveBaseClient ac("move_base", true);
  
  while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  move_base_msgs::MoveBaseGoal goal;
  
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  /*Pick & Drop Positions*/

  double pick_pos_x = -4.0;
  double pick_pos_y = 4.0;
  double drop_pos_x = -4.0;
  double drop_pos_y = 1.0;

  goal.target_pose.pose.position.x = pick_pos_x;
  goal.target_pose.pose.position.y = pick_pos_y;
  goal.target_pose.pose.orientation.w = 1.0;
  
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);
  
  ac.waitForResult();
  
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Picked Parcel!");
  else
    ROS_INFO("The base failed to move.");
    
  ros::Duration(5.0).sleep();

  goal.target_pose.pose.position.x = drop_pos_x;
  goal.target_pose.pose.position.y = drop_pos_y;
  goal.target_pose.pose.orientation.w = -1.57;
  
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);
  
  ac.waitForResult();
  
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Dropped Parcel!");
  }  
  else
    ROS_INFO("The Base Failed To Move!");
    
  ros::Duration(5.0).sleep();
  
  return 0;
}
