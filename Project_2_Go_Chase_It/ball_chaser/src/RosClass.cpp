#include <RosClass.h>

RosClass::RosClass()
{
    /*Publishers*/ 
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10); 
    /*Subscribers*/

}

RosClass::~RosClass()
{}

void RosClass::sendMotorCommand(geometry_msgs::Twist motor_command)
{
    motor_command_publisher.publish(motor_command);
}

void RosClass::CameraCallback(const sensor_msgs::Image img);
{
    m_Image = img;
}

/* Getters */
RosClass::GetImageData()
{
    return m_Image;
}