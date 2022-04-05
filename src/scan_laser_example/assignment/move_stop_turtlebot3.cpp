#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include "../laserscan/LaserScanner.h"

using namespace std;

sensor_msgs::LaserScan _scanMsg;
ros::Subscriber scanSubscriber;
ros::Publisher controlled_cmd_vel_publ;
geometry_msgs::Twist cmd_vel_command;
// bool Obstacle;


void scanCallback(sensor_msgs::LaserScan scanMessage);
bool moveStraightUntilObstacle(sensor_msgs::LaserScan scanMessage);
void rotateUntilNoObstacle(sensor_msgs::LaserScan scanMessage, bool Obstacle);

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
		double distance = LaserScanner::getMinimumFrontRange(_scanMsg,5,5);
		bool Obstacle = moveStraightUntilObstacle(_scanMsg);
		rotateUntilNoObstacle(_scanMsg,Obstacle);
		
}

bool moveStraightUntilObstacle(sensor_msgs::LaserScan scanMessage){

	if (LaserScanner::getMinimumFrontRange(scanMessage,5,5) < 0.6){
		cmd_vel_command.linear.x =0.0;
		// cmd_vel_command.angular.z=0.0;
		controlled_cmd_vel_publ.publish(cmd_vel_command);
		ROS_INFO("Front distance minimum reached!! [%2.2f], linear Vel x [%2.2f] ", 
										LaserScanner::getMinimumFrontRange(scanMessage,5,5), 
										cmd_vel_command.linear.x);
		return true;
	} else{
		cmd_vel_command.linear.x =0.1;
		cmd_vel_command.angular.z=0;
		controlled_cmd_vel_publ.publish(cmd_vel_command);
		ROS_INFO("linear vel x [%2.2f]",cmd_vel_command.linear.x);
		return false;

	}
}

void rotateUntilNoObstacle(sensor_msgs::LaserScan scanMessage, bool Obstacle_true=true){
	// ROS_INFO_STREAM("Inside rotate Obstacle: "<< Obstacle_true);
	double distance_front = LaserScanner::getMinimumFrontRange(scanMessage,5,5);
	if (Obstacle_true){
			// ros::Rate loop_rate(10);
		while (ros::ok()){
			cmd_vel_command.linear.x =0.0;
			cmd_vel_command.angular.z=0.5;
			ROS_INFO("Angular vel [%2.2f], distance: [%2.2f],",cmd_vel_command.angular.z, 
															   distance_front);
			controlled_cmd_vel_publ.publish(cmd_vel_command);
			// ros::Duration(1).sleep();
			ros::spinOnce();
			ROS_INFO("distance_front: [%2.2f], _scanMsg: [%2.2f]",distance_front,LaserScanner::getMinimumFrontRange(_scanMsg,5,5));
			if (LaserScanner::getMinimumFrontRange(_scanMsg,5,5)> 3){
				break;
			}
			// loop_rate.sleep(); 
			// ROS_INFO_STREAM("distance "<< LaserScanner::getMinimumFrontRange(scanMessage,5,5))
			// if (LaserScanner::getMinimumFrontRange(scanMessage,5,5) > 0.6 ){
			// 	break;
			// }
		}
	} else{
		ROS_INFO_STREAM("no obstacle");
	}
	// return true;
}
