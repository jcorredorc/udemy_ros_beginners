#!/usr/bin/env python 

import rospy
from geometry_msgs.msg import Twist
#task 1. import the Pose type from the module turtlesim 
from turtlesim.msg import Pose
import math 
import time 
from std_srvs.srv import Empty

x=0 
y=0 
z=0 
yaw=0 

def poseCallback(pose_message):

    #task 4. display the x, y, and theta received from the message 
    # print "pose callback" 
    rospy.loginfo(rospy.get_caller_id()+"Pose Callback")
    rospy.loginfo("x = " + str(pose_message.x))
    rospy.loginfo("y = " + str(pose_message.y))
    rospy.loginfo("yaw = " + str(pose_message.theta))
    # print ('y = %f' %) 
    # print ('yaw = '.%)  

if __name__ == '__main__':
    try:
        rospy.init_node('turtlesim_motion_pose', anonymous=True)

        #task 2. subscribe to the topic of the pose of the Turtlesim 
        rospy.Subscriber("/turtle1/pose",Pose,poseCallback)
        #task 3. spin 
        rospy.spin()

    except rospy.ROSInterruptException:
        rospy.loginfo("node terminated.")