# [udemy_ros_beginners](https://www.udemy.com/course/ros-essentials/)

ROS Noetic - Ubuntu 20.04 





| folder src| content |
| ------------- | ------------- |
| [control_motion_turtlesim](src/control_motion_turtlesim/) | * turtlesim_pose.py: subscribe the turtlesim pose topic and show it  <br/> * turtlesim_vel.py: move turtlesim certain distance and stop  |
|[iot_sensor](src/iot_sensor/) | use a custom message [IoTSensor.msg](msg/IoTSensor.msg), publish and subscribe iot msg  |
|[service_example](src/service_example/)|a service that calculate the area of a rectangle, given its width and height. See the definition of the service type in [srv file](srv/rectangleAreaService.srv)|
|[opencv_example](src/opencv_example/)| **Python** <br/> * open_copy.py <br/> * image_structure.py <br/> * images_encoding.py <br/> * read_video.py <br/> * image_draw.py <br/> * image_pub_sub.py (bridge w ROS) <br/>  * image_thresholding.py (segmentation) <br/> * color_filtering.py <br/> * contours_detection.py <br/> * contours_processing.py <br/> * ball_detection.py <br/>  **C++**  <br/>  * read_video.cpp <br/>  * open_copy.cpp <br/> * image_pub_sub.cpp <br/>  *  trackbar_video.cpp (book learning OpenCV) <br/> **Assignments** <br/> * read_video_ball_tracker.cpp  <br/> * tennis_ball_publisher.cpp <br/> * tennis_ball_listener.cpp <br/> * tennis_ball_usb_cam_tracker.cpp  |
|[scan_laser_example](src/scan_laser_example/)|* scan_subscriber.py <br/> * scan_subscriber.cpp <br/> * laserscan: A custom library from the [course material](https://www.udemy.com/course/ros-essentials/)|