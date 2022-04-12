# [udemy_ros_beginners](https://www.udemy.com/course/ros-essentials/)

ROS Noetic - Ubuntu 20.04 

This repository is solely for storing notes on the udemy course's personal learning process; please refer to [the original source](https://www.udemy.com/course/ros-essentials/) for more information.

| folder src| content |
| ------------- | ------------- |
| [control_motion_turtlesim](src/control_motion_turtlesim/) | * turtlesim_pose.py: subscribe the turtlesim pose topic and show it  <br/> * turtlesim_vel.py: move turtlesim certain distance and stop  |
|[iot_sensor](src/iot_sensor/) | use a custom message [IoTSensor.msg](msg/IoTSensor.msg), publish and subscribe iot msg  |
|[service_example](src/service_example/)|a service that calculate the area of a rectangle, given its width and height. See the definition of the service type in [srv file](srv/rectangleAreaService.srv)|
|[opencv_example](src/opencv_example/)| **Python** <br/> * open_copy.py <br/> * image_structure.py <br/> * images_encoding.py <br/> * read_video.py <br/> * image_draw.py <br/> * image_pub_sub.py (bridge w ROS) <br/>  * image_thresholding.py (segmentation) <br/> * color_filtering.py <br/> * contours_detection.py <br/> * contours_processing.py <br/> * ball_detection.py <br/>  **C++**  <br/>  * read_video.cpp <br/>  * open_copy.cpp <br/> * image_pub_sub.cpp <br/>  *  trackbar_video.cpp (book learning OpenCV) <br/> **Assignments** <br/> * read_video_ball_tracker.cpp  <br/> * tennis_ball_publisher.cpp <br/> * tennis_ball_listener.cpp <br/> * tennis_ball_usb_cam_tracker.cpp  |
|[scan_laser_example](src/scan_laser_example/)|* scan_subscriber.py <br/> * scan_subscriber.cpp <br/> * robot_stops_obstacle.py :x: <br/> * laserscan: A custom library from the [course material](https://www.udemy.com/course/ros-essentials/) <br/> **Assignment** <br/> * move_stop_turtlebot3.cpp <br/> * move_stop_turtlebot3.py <br/>  * move_pid_turtlebot3.cpp <br/> * move_pid_turtlebot3.py |
|[arduino](src/arduino/.)| __hcsr04_ros.ino__ compile and load in the arduino IDE.  |

## Usage

clone this repository in your workspace and compile it,
```
git clone  https://github.com/jcorredorc/udemy_ros_beginners.git
```
install xterm:

```
sudo apt install xterm
```

### OpenCV

* Launch basic example publisher and listener
    ```
    roslaunch udemy_ros_beginners image_pub_sub.launch
    ```
* Launch realsense2 camera and convert to laser scan topic

    ```
    roslaunch udemy_ros_beginners depth_image_to_laser.launch
    ```
* Launch usb camera test
    ```
    roslaunch udemy_ros_beginners usb_cam-test.launch
    ```

1. Assignment:

* Using openCV without ROS
    ```
    rosrun udemy_ros_beginners read_video_ball_tracker_cpp
    ```
*  Using OpenCV + ROS and Reading from a Video File (CvBridge)
    ```
    roslaunch udemy_ros_beginners videofile_pub_sub.launch 
    ```
* Using OpenCV + ROS and Reading from a USB Camera (CvBridge)
    ```
    roslaunch udemy_ros_beginners usb_cam-test.launch
    rosrun udemy_ros_beginners tennis_ball_usb_cam_tracker_cpp
    ```

### Laser Scan 

1. Assignment C++ and Python: 
    * Move turtlebot3 straight until reached an obstacle. Then rotates until the straight obstacle distance becomes greater than 3 meters.  

    ```
    rosrun udemy_ros_beginners turtlebot3_start.sh
    ```
    - Test the functions in other map

    ```
    rosrun udemy_ros_beginners turtlebot3_start_house.sh
    ```
    *  Proportional controller that regulates the angular speed and the linear speed such as it moves smoothly without hitting obstacles.

    ```
    rosrun udemy_ros_beginners turtlebot3_pid_start.sh
    ```

    * Test the proportional controller in other map

    ```
    rosrun udemy_ros_beginners turtlebot3_pid_start_house.sh
    ```

        >  Play with parameters: left_angle, right_angle and proportional gain (Prop). 

