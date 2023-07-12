#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <sensor_msgs/Image.h>

typedef message_filters::sync_policies::ExactTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;

ros::Publisher depth_pub;
ros::Publisher color_pub;

void callback(const sensor_msgs::ImageConstPtr& depth, const sensor_msgs::ImageConstPtr& color)
{
  // Publish the synchronized depth and color images
  depth_pub.publish(depth);
  color_pub.publish(color);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "kinect_sync_node");

  ros::NodeHandle nh;

  message_filters::Subscriber<sensor_msgs::Image> depth_sub(nh, "/kinect2/sd/image_depth_rect", 1);
  message_filters::Subscriber<sensor_msgs::Image> color_sub(nh, "/kinect2/hd/image_color_rect", 1);

  // Create publishers
  depth_pub = nh.advertise<sensor_msgs::Image>("/synced_depth", 1);
  color_pub = nh.advertise<sensor_msgs::Image>("/synced_color", 1);

  message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), depth_sub, color_sub);
  sync.registerCallback(boost::bind(&callback, _1, _2));

  ros::spin();

  return 0;
}
