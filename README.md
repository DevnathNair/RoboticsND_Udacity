# RoboticsND_Udacity
Udacity's Robotics Software Engineer Nanodegree Program - A collection of coursework and projects submitted during the course of the program.

## Project #1: Build My World

![Build_My_World](Project_1_Build_My_World/Udacity_Project_1_World.png)

### Description

The introductory project of Udacity's Robotics Nanodegree; It required building a simulated "world" in Gazebo that consisted of a house-like structure that houses robots to be developed in subsequent projects. A plugin was built that would execute on launching the world.

### Concepts
Concepts explored in this project:

  - Gazebo Worlds
  - Gazebo Models
  - Gazebo Plugins
  
## Project #2: Go Chase It

![Go_Chase_It_Animation](Project_2_Go_Chase_It/Udacity_Poject_2_Go_Chase_It.gif.gif)

## Description

Project 2 called for a robot to be generated from an Xacro file and spawned in the Gazebo World. This robot would then follow a white ball within the world built in Project 1. 
- The ```process_image``` node sends a serivce request to the ```drive_robot``` node which then publishes linear and angular velocity commands to a ```/cmd_vel``` topic to drive the robot left,forward or right based on the position of the ball ascertained by a camera placed on it.
- The differential drive controller for the robot was included in coursework resources.

## Concepts
Concepts explored in this project:

  - ROS Publishers, Subscribers & Services and their interactions in C++  
  - Generation of Robot Models from Xacro files using the URDF spawner
  - ROS message types

