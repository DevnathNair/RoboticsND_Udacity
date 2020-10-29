#ifndef ROS_CLASS_H
#define ROS_CLASS_H

#include <ros/ros.h>
#include <ros/console.h>

class RosClass
{
public:

    /* Constructor for the Ros class */ 
    RosClass();
     /* Destructor for the Ros class */
    ~RosClass();
    
    /*GETTERS*/
    void RosClass::CameraCallback(const sensor_msgs::Image img);




    /*SETTERS*/
    void RosClass::sendVelocityCmd();
   
    

private:
     /**
    * @brief NodeHandle ROS
    */
    ros::NodeHandle n;
       
    /*SUBSCRIBERS*/
    ros::Subscriber sub1; // odometry subscriber.
    
    /*PUBLISHERS*/
     // publisher handler to publish velocities to robot.
    ros::Publisher motor_command_publisher;

    sensor_msgs::Image m_image;