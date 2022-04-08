#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include "../laserscan/LaserScanner.h"

using namespace std;

sensor_msgs::LaserScan _scanMsg;
ros::Subscriber scanSubscriber;
ros::Publisher controlled_cmd_vel_publ;
geometry_msgs::Twist cmd_vel_command;

// float right_angle=30, left_angle=30, Prop=0.5;
float right_angle = 5, left_angle = 5, Prop = 0.5;

void scanCallback(sensor_msgs::LaserScan scanMessage);
bool moveStraightUntilObstacle(sensor_msgs::LaserScan scanMessage);
void rotateUntilNoObstacle(sensor_msgs::LaserScan scanMessage, bool Obstacle);
void publish_vel_command(float speed, float angle);

int main(int argc, char **argv)
{

	// initialize the ROS node
	ros::init(argc, argv, "move_stop_turtlebot3_cpp");
	ros::NodeHandle n;

	// subscribe to the laser scanner topic
	scanSubscriber = n.subscribe("/scan", 10, scanCallback);
	controlled_cmd_vel_publ = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

	ros::spin();
}

void scanCallback(sensor_msgs::LaserScan scanMessage)
{
	_scanMsg = scanMessage;
	// double distance = LaserScanner::getMinimumFrontRange(scanMessage,5,5);
	bool Obstacle = moveStraightUntilObstacle(scanMessage);
	rotateUntilNoObstacle(scanMessage, Obstacle);
}

bool moveStraightUntilObstacle(sensor_msgs::LaserScan scanMessage)
{
	// Prop = 0.5;
	if (LaserScanner::getMinimumFrontRange(_scanMsg, left_angle, right_angle) < 0.6)
	{
		publish_vel_command(0, 0);
		ROS_INFO("Front distance minimum reached!! [%2.2f]",
				 LaserScanner::getMinimumFrontRange(_scanMsg, left_angle, right_angle));
		return true;
	}
	else
	{
		// 0.6 is the value for the distance between robot and obstacle
		publish_vel_command(-Prop * (0.6 - LaserScanner::getMinimumFrontRange(_scanMsg, left_angle, right_angle)), 0);
		return false;
	}
}

void rotateUntilNoObstacle(sensor_msgs::LaserScan scanMessage, bool Obstacle_true = true)
{
	float angle_vel = 0;
	if (Obstacle_true)
	{
		// ros::Rate loop_rate(10);
		while (ros::ok())
		{
			ros::spinOnce();
			if (LaserScanner::getMinimumRangeLeft(_scanMsg, left_angle) <
				LaserScanner::getMinimumRangeRight(_scanMsg, right_angle))
			{
				angle_vel = 0.3;
			}
			else
			{
				angle_vel = -0.3;
			}
			// 0.6 is the value for the distance between robot and obstacle
			publish_vel_command(-Prop * (0.6 - LaserScanner::getMinimumFrontRange(_scanMsg, left_angle, right_angle)), angle_vel);
			ros::Duration(1).sleep();
			if (LaserScanner::getMinimumFrontRange(_scanMsg, left_angle, right_angle) > 3)
			{
				break;
			}
			// loop_rate.sleep();
		}
	}
	else
	{
		ROS_INFO_STREAM("no obstacle rotating");
	}
}

void publish_vel_command(float speed, float angle)
{
	// Saturation at max_speed ------------
	float max_speed = 0.26;
	int sign = 0;
	if (speed >= 0)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	if (abs(speed) > max_speed)
	{
		speed = sign * max_speed;
	}
	//-------------------------------
	cmd_vel_command.linear.x = speed;
	cmd_vel_command.angular.z = angle;
	controlled_cmd_vel_publ.publish(cmd_vel_command);
	ROS_INFO("Linear vel [%2.2f] | Angular vel [%2.2f]", cmd_vel_command.linear.x, cmd_vel_command.angular.z);
}