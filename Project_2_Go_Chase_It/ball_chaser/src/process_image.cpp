//Udacity Project 2 - Go Chase It
//Segments camera data into three zones so as to determine the direction in which the robot should traverse in

#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "sensor_msgs/Image.h"
#include <RosClass.h"


//Global robot parameters
float LINEAR_VEL = 0.8;
float ANGULAR_VEL = 4;
//Behaviour Flag
#define RECOVERY_BEHAVIOUR 1

ros::ServiceClient client;

void drive_robot(float linearx, float angularz)
{
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = linearx;
    srv.request.angular_z = angularz;
    client.call(srv);
}

void process_image()
{
    RosClass SAPObject;
    m_image = SAPObject.GetImageData();

    int pixel_max = 255;
    int width_pos = 0;
    int white_pixel_count = 0;
    int width_pos_sum = 0;
    //Fixed Camera Angle, scan a thin portion of the image, reducing computation time
    int search_start = m_image.data.size()*4/9;
    int search_end = m_image.data.size()*5/9-2;
    //std::cout << boost::typeindex::type_id<decltype(m_image.width)>().pretty_name() << std::endl;
    
	for(int i=search_start;i<search_end;i++)
    	{	
        //m_image.data.size contains individual RGB values, have to ensure that R,G,B is 255 else, a fully R or G or B ball will be detected.
        if((int)m_image.data[i] == pixel_max && (int)m_image.data[i+1] == pixel_max && (int)m_image.data[i+2] == pixel_max)
        {
           width_pos = (i%(m_image.width*3))/3;
           width_pos_sum += width_pos;
           white_pixel_count += 1;
        }
    }

}

//Callback to process image data
void process_image_callback(const sensor_msgs::Image img)
{
    int pixel_max = 255;
    int width_pos = 0;
    int white_pixel_count = 0;
    int width_pos_sum = 0;
    //Fixed Camera Angle, scan a thin portion of the image, reducing computation time
    int search_start = img.data.size()*4/9;
    int search_end = img.data.size()*5/9-2;
    //std::cout << boost::typeindex::type_id<decltype(img.width)>().pretty_name() << std::endl;
    
	for(int i=search_start;i<search_end;i++)
    	{	
        //img.data.size contains individual RGB values, have to ensure that R,G,B is 255 else, a fully R or G or B ball will be detected.
        if((int)img.data[i] == pixel_max && (int)img.data[i+1] == pixel_max && (int)img.data[i+2] == pixel_max)
        {
           width_pos = (i%(img.width*3))/3;
           width_pos_sum += width_pos;
           white_pixel_count += 1;
        }
    }
      
//Bot Behaviour 
if(RECOVERY_BEHAVIOUR == 1 && white_pixel_count == 0)
	{
	drive_robot(0,ANGULAR_VEL*10);
	std::cout<<"FINDING BALL"<<std::endl;
	}
else if (white_pixel_count == 0)
    {
        drive_robot(0,0);
        std::cout<<"STOP"<<std::endl;            
    }
        
    else 
    {
        int img_x = width_pos_sum / white_pixel_count;
        if (img_x < (int) img.width/3)
        {
        drive_robot(LINEAR_VEL,ANGULAR_VEL);
        std::cout<<"LEFT"<<std::endl;}
        else if (img_x > (int) img.width*2/3)
        {drive_robot(LINEAR_VEL,-ANGULAR_VEL);
        std::cout<<"RIGHT"<<std::endl;}
        else 
        {drive_robot(LINEAR_VEL,0.0);
        std::cout<<"FORWARD"<<std::endl;}
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;
    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
    ros::spin();
    return 0;
}

