#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include "../laserscan/LaserScanner.h"
// #include "../laserscan/utility_lib.h"

using namespace std;

sensor_msgs::LaserScan _scanMsg;
ros::Subscriber scanSubscriber;
ros::Publisher controlled_cmd_vel_publ;
geometry_msgs::Twist cmd_vel_command;
// bool Obstacle;
float right_angle=5, left_angle=5, Prop=0.5;

void scanCallback(sensor_msgs::LaserScan scanMessage);
bool moveStraightUntilObstacle(sensor_msgs::LaserScan scanMessage);
void rotateUntilNoObstacle(sensor_msgs::LaserScan scanMessage, bool Obstacle);
void publish_vel_command(float speed, float angle);

int main(int argc, char **argv){

	//initialize the ROS node
	ros::init(argc, argv, "move_stop_turtlebot3_cpp");
	ros::NodeHandle n;

	//subscribe to the laser scanner topic
	scanSubscriber = n.subscribe("/scan", 10, scanCallback);
	controlled_cmd_vel_publ = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
	
	ros::spin();
}

void scanCallback (sensor_msgs::LaserScan scanMessage){
		_scanMsg = scanMessage;
		// double distance = LaserScanner::getMinimumFrontRange(scanMessage,5,5);
		bool Obstacle = moveStraightUntilObstacle(scanMessage);
		rotateUntilNoObstacle(scanMessage,Obstacle);
		
}

bool moveStraightUntilObstacle(sensor_msgs::LaserScan scanMessage){
	// Prop = 0.5;
	if (LaserScanner::getMinimumFrontRange(_scanMsg,left_angle,right_angle) < 0.6){
		// cmd_vel_command.linear.x =0.0;
		// // cmd_vel_command.angular.z=0.0;
		// controlled_cmd_vel_publ.publish(cmd_vel_command);
		publish_vel_command(0,0);
		ROS_INFO("Front distance minimum reached!! [%2.2f]", 
						LaserScanner::getMinimumFrontRange(_scanMsg,left_angle,right_angle));
		return true;
	} else{
		// cmd_vel_command.linear.x =-0.5*(0.6-LaserScanner::getMinimumFrontRange(_scanMsg,5,5));
		// cmd_vel_command.angular.z=0;
		// controlled_cmd_vel_publ.publish(cmd_vel_command);
		// ROS_INFO("linear vel x [%2.2f]",cmd_vel_command.linear.x);
		publish_vel_command(-Prop*(0.6-LaserScanner::getMinimumFrontRange(_scanMsg,left_angle,right_angle)),0);
		return false;

	}
}

void rotateUntilNoObstacle(sensor_msgs::LaserScan scanMessage, bool Obstacle_true=true){
	// ROS_INFO_STREAM("Inside rotate Obstacle: "<< Obstacle_true);
	// double distance_front = LaserScanner::getMinimumFrontRange(scanMessage,5,5);
	float angle_vel=0;
	if (Obstacle_true){
			// ros::Rate loop_rate(10);
		while (ros::ok()){
			ros::spinOnce();
			// cmd_vel_command.angular.z=0.3;
			if (LaserScanner::getMinimumRangeLeft(_scanMsg,left_angle) < LaserScanner::getMinimumRangeRight(_scanMsg,right_angle)){
				angle_vel = 0.3;
				// cmd_vel_command.angular.z=0.3;
				// ros::Duration(1).sleep();
			}
			else{
				angle_vel = -0.3;
				// cmd_vel_command.angular.z=-0.3;
			}
			// cmd_vel_command.linear.x=-0.5*(0.6-LaserScanner::getMinimumFrontRange(_scanMsg,left_angle,right_angle));
			// controlled_cmd_vel_publ.publish(cmd_vel_command);
			//  ROS_INFO("Linear vel [%2.2f] | Angular vel [%2.2f]",cmd_vel_command.linear.x,
			//  													 cmd_vel_command.angular.z);
			publish_vel_command(-Prop*(0.6-LaserScanner::getMinimumFrontRange(_scanMsg,
													left_angle,right_angle)),
													angle_vel);
			ros::Duration(1).sleep();
			// ros::Duration(1).sleep();
			// ROS_INFO("_scanMsg: [%2.2f]",LaserScanner::getMinimumFrontRange(_scanMsg,5,5));
			if (LaserScanner::getMinimumFrontRange(_scanMsg,left_angle,right_angle)> 3){
				break;
			}
			// loop_rate.sleep(); 
			// ROS_INFO_STREAM("distance "<< LaserScanner::getMinimumFrontRange(scanMessage,5,5))
			// if (LaserScanner::getMinimumFrontRange(scanMessage,5,5) > 0.6 ){
			// 	break;
			// }
		}
	} else{
		ROS_INFO_STREAM("no obstacle rotating");
	}
	// return true;
}

void publish_vel_command(float speed, float angle){
	// Saturation at 1.0 ------------
	float max_speed = 1.0;
	int sign =0;
	if (speed >=0){
		sign=1;
	}else{
		sign=-1;
	}
	if (abs(speed) > max_speed){
		speed = sign*max_speed;
	}
	//-------------------------------	
	cmd_vel_command.linear.x = speed;
	cmd_vel_command.angular.z= angle;
	controlled_cmd_vel_publ.publish(cmd_vel_command);
	ROS_INFO("Linear vel [%2.2f] | Angular vel [%2.2f]",cmd_vel_command.linear.x,
			 													 cmd_vel_command.angular.z);
}