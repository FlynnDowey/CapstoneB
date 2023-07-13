#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

double encoder0Pos = 0;
double encoder1Pos = 0;
double encoder2Pos = 0;
double encoder3Pos = 0;

void encoder0Callback(const std_msgs::Int32::ConstPtr& msg)
{
    encoder0Pos = static_cast<double>(msg->data);
}

void encoder1Callback(const std_msgs::Int32::ConstPtr& msg)
{
    encoder1Pos = static_cast<double>(msg->data);
}

void encoder2Callback(const std_msgs::Int32::ConstPtr& msg)
{
    encoder2Pos = static_cast<double>(msg->data);
}

void encoder3Callback(const std_msgs::Int32::ConstPtr& msg)
{
    encoder3Pos = static_cast<double>(msg->data);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odometry_publisher");

    ros::NodeHandle n;
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 100);

    ros::Subscriber sub_enc0 = n.subscribe("encoder0", 50, encoder0Callback);
    ros::Subscriber sub_enc1 = n.subscribe("encoder1", 50, encoder1Callback);
    ros::Subscriber sub_enc2 = n.subscribe("encoder2", 50, encoder2Callback);
    ros::Subscriber sub_enc3 = n.subscribe("encoder3", 50, encoder3Callback);

    double x = 0.0;
    double y = 0.0;
    double th = 0.0;

    double vx = 0.0;
    double vy = 0.0;
    double vth = 0.0;

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();

    ros::Rate r(1.0);
    double old_encoder0Pos = 0, old_encoder1Pos = 0, old_encoder2Pos = 0, old_encoder3Pos = 0;
    double wheel_radius = 0.048; // radius of the wheel in meters
    double encoder_resolution = 537.7; // encoder counts per revolution
    double wheelbase = 0.220 + 0.0185; // distance between wheels along the x-axis in meters
    double track = 0.120; // distance between wheels along the y-axis in meters

    while (ros::ok()) {
        ros::spinOnce();

        current_time = ros::Time::now();
        double dt = (current_time - last_time).toSec();

        if (dt <= 0) {
            // If the time difference is zero or negative, skip the rest of this loop iteration
            continue;
        }

        // Calculate the wheel velocities in m/s
        double wheel1_velocity = ((encoder0Pos - old_encoder0Pos) / encoder_resolution) * (2 * M_PI * wheel_radius) / dt;
        double wheel2_velocity = ((encoder1Pos - old_encoder1Pos) / encoder_resolution) * (2 * M_PI * wheel_radius) / dt;
        double wheel3_velocity = ((encoder2Pos - old_encoder2Pos) / encoder_resolution) * (2 * M_PI * wheel_radius) / dt;
        double wheel4_velocity = ((encoder3Pos - old_encoder3Pos) / encoder_resolution) * (2 * M_PI * wheel_radius) / dt;

        // Assuming a holonomic drive robot (omni-directional), calculate linear and angular velocities
        vx = (wheel1_velocity + wheel2_velocity + wheel3_velocity + wheel4_velocity) / 4.0; // X-axis linear velocity
        vy = (-wheel1_velocity + wheel2_velocity + wheel3_velocity - wheel4_velocity) / 4.0; // Y-axis linear velocity
        vth = (-wheel1_velocity + wheel2_velocity - wheel3_velocity + wheel4_velocity) / (4.0 * wheelbase); // Z-axis angular velocity

        old_encoder0Pos = encoder0Pos;
        old_encoder1Pos = encoder1Pos;
        old_encoder2Pos = encoder2Pos;
        old_encoder3Pos = encoder3Pos;

        x += vx * dt;
        y += vy * dt;
        th += vth * dt;

        // since all odometry is 6DOF we'll need a quaternion created from yaw
        geometry_msgs::Quaternion odom_quat;
        odom_quat.x = 0.0;
        odom_quat.y = 0.0;
        odom_quat.z = 0.0;
        odom_quat.w = th;

        // next, we'll publish the odometry message over ROS
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        // odom.header.frame_id;

        // set the position
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = odom_quat;

        // set the velocity
        // odom.child_frame_id = "base_footprint";
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.linear.y = vy;
        odom.twist.twist.angular.z = vth;

        // publish the message
        odom_pub.publish(odom);

        last_time = current_time;
        r.sleep();
    }

    return 0;
}
