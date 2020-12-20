/*
Devnath Nair
Udacity Robotics ND Program
Project 5 : Home Service Robot
*/


#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

/*Pick & Drop between tables*/

/*Pick and Drop Positions*/
double pick_pos_x = -4.0;
double pick_pos_y = 4.0;
double drop_pos_x = -4.0;
double drop_pos_y = 1.0;

//State Flags
bool parcel_pick = false;
bool parcel_drop = false;

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_time");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  visualization_msgs::Marker marker;

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "cube";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = pick_pos_x;
  marker.pose.position.y = pick_pos_y;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 0.2;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 1.0f;
  marker.color.g = 0.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration(5);
  while (ros::ok())
  {
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Waiting for Marker Subscriber!");
      sleep(1);
    }
    
    /*Publish and delete the two markers with a time delay*/
    
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
      
      ros::Duration(10).sleep();  
      
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      
      marker.pose.position.x = drop_pos_x;
      marker.pose.position.y = drop_pos_y;
      
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
      
      ros::Duration(100).sleep();
    
    
    ros::spinOnce();
  }
}
