#!/usr/bin/env python

import sys
from turtle import width
import rospy
from udemy_ros_beginners.srv import rectangleAreaService
from udemy_ros_beginners.srv import rectangleAreaServiceRequest
from udemy_ros_beginners.srv import rectangleAreaServiceResponse

def area_rectangle_client(x, y):
    rospy.wait_for_service('area_rectangle')
    try:
        area_rectangle = rospy.ServiceProxy('area_rectangle', rectangleAreaService)
        resp1 = area_rectangle(x, y)
        return resp1.area
    except rospy.ServiceException(e):
        print ("Service call failed: %s"%e)

def usage():
    return 

if __name__ == "__main__":
    if len(sys.argv) == 3:
        width = int(sys.argv[1])
        height = int(sys.argv[2])
    else:
        print ("%s please pass the [width height] arguments"%sys.argv[0])
        sys.exit(1)
    print("Requesting rectangle area width: %s and height: %s"%(width, height))
    area = area_rectangle_client(width, height)
    print("%s * %s = %s"%(width, height, area))