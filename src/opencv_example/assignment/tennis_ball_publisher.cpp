#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "opencv2/opencv.hpp"

//#include <string.h>

using namespace cv;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tennis_ball_publisher_node");
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_(nh_);
  image_transport::Publisher image_pub_ = it_.advertise("tennis_ball_image", 1);
  // cv_bridge::CvImagePtr cv_ptr;
  sensor_msgs::ImagePtr msg;

  // VideoCapture video_capture(0); // open the default camera}
  VideoCapture vid("/home/javier/catkin_ws/src/udemy_ros_beginners/src/opencv_example/video/tennis-ball-video.mp4");
  int num_frames = (int)vid.get(cv::CAP_PROP_FRAME_COUNT);

  if (!vid.isOpened())
  {  // check if we succeeded
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }

  while (ros::ok())
  {
    Mat frame;
    // Mat hsv_frame;
    // Mat maskHSV, resultHSV;

    // Capture frame-by-frame
    vid >> frame;
    // vid.read(frame)
    // loop restart the video if reached last frame
    if ((int)vid.get(CAP_PROP_POS_FRAMES) >= num_frames)
    {
      std::cout << "last frame reached: " << num_frames << std::endl;
      vid.set(CAP_PROP_POS_FRAMES, 1);
    }

    // if the frame is empty, break
    if (frame.empty())
    {
      std::cout << "empty video stream or file" << std::endl;
      break;
    }
    // Display the resulting frame
    imshow("Frame RAW", frame);

    // publish the image in ros topic
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
    image_pub_.publish(msg);

    if (waitKey(30) >= 0)
      break;
  }

  // when everything done, release the video capture object
  vid.release();

  // Close all the frames
  destroyAllWindows();

  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}