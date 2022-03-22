#!/usr/bin/env python

from udemy_ros_beginners.srv import rectangleAreaService
from udemy_ros_beginners.srv import rectangleAreaServiceRequest
from udemy_ros_beginners.srv import rectangleAreaServiceResponse

import rospy

def handle_area_rectangle(req):
    print ("Returning [%s * %s = %s]"%(req.width, req.height, (req.width * req.height)))
    return rectangleAreaServiceResponse(req.width * req.height)

def calc_area_rectangle_server():
    rospy.init_node('area_rectangle_server')
    s = rospy.Service('area_rectangle', rectangleAreaService, handle_area_rectangle)
    print ("Ready to calculate the rectangle area.")
    rospy.spin()
    
if __name__ == "__main__":
    calc_area_rectangle_server()