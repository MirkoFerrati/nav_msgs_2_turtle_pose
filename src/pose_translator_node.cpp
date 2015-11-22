#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "nav_msgs/Odometry.h"


ros::Publisher pub;

void poseCallback(const nav_msgs::Odometry::ConstPtr & pose)
{
  turtlesim::Pose msg;
  msg.x=pose->pose.pose.position.x;
  msg.y=pose->pose.pose.position.y;
  msg.theta=pose->pose.pose.orientation.z;
  msg.linear_velocity=pose->twist.twist.linear.x;
  msg.angular_velocity=pose->twist.twist.angular.z;
  pub.publish(msg);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "pose_translator");

    ros::NodeHandle nh;
    pub = nh.advertise<turtlesim::Pose>("pose",10);
    ros::Subscriber sub = nh.subscribe<nav_msgs::Odometry>("odom",10,poseCallback);
    
    ros::spin();
    return 0;
}