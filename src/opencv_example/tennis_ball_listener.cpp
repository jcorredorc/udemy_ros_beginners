#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

static const std::string OPENCV_WINDOW = "OpenCV image";

namespace cv
{
void tracking_ball(Mat& frame)
{
  // cv::Mat frame;
  Mat hsv_frame;
  Mat maskHSV, resultHSV;
  // cv::imshow("via trackingBall", frame);

  // filter color ------------

  cvtColor(frame, hsv_frame, COLOR_BGR2HSV);
  imshow("Frame HSV", hsv_frame);

  //#find the upper and lower bounds of the yellow color (tennis ball)
  Scalar yellowLower = Scalar(30, 150, 100);
  Scalar yellowUpper = Scalar(50, 255, 255);

  // #define a mask using the lower and upper bounds of the yellow color
  inRange(hsv_frame, yellowLower, yellowUpper, maskHSV);
  imshow("Mask HSV", maskHSV);
  // optional...
  // bitwise_and(hsv_frame,hsv_frame,resultHSV, maskHSV);
  // imshow("resultHSV",resultHSV);

  // get contours ------------
  std::vector<std::vector<Point> > contours;  // list of contour points
  std::vector<Vec4i> hierarchy;
  // findContours
  findContours(maskHSV, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  // draw ball contours *******************************************************

  // using convexHull ; Find the convex Hull  -----
  // create hull array for convex hull points
  std::vector<std::vector<Point> > hull(contours.size());
  for (int i = 0; i < contours.size(); i++)
    convexHull(Mat(contours[i]), hull[i], false);

  // draw hull array ----------------------------------------
  // create a blank image (black image)
  Mat drawing = Mat::zeros(maskHSV.size(), CV_8UC3);
  for (int i = 0; i < contours.size(); i++)
  {
    Scalar color_contours = Scalar(0, 255, 0);  // green - color for contours
    Scalar color = Scalar(255, 0, 0);           // blue - color for convex hull
    // draw ith contour
    drawContours(drawing, contours, i, color_contours, 1, 8, std::vector<Vec4i>(), 0, Point());
    // draw ith convex hull
    drawContours(drawing, hull, i, color, 1, 8, std::vector<Vec4i>(), 0, Point());
  }
  // imshow("countors",drawing);

  // draw a circle  -----------------------------------------------
  // RNG rng(12345); // random color
  std::vector<Point2f> centers(contours.size());
  std::vector<float> radius(contours.size());
  // Mat black_image = Mat::zeros(maskHSV.size(),CV_8UC3);
  for (int i = 0; i < contours.size(); i++)
  {
    double area = contourArea(contours[i]);
    double perimeter = arcLength(contours[i], true);
    //((x, y), radius) = minEnclosingCircle(c)
    minEnclosingCircle(contours[i], centers[i], radius[i]);
    // std::cout << "area: " << area << std::endl;
    if (area > 2800)
    {
      circle(drawing, centers[i], (int)radius[i], CV_RGB(0, 255, 0), 2);
      putText(drawing, std::to_string(area),
              centers[i],                  // Coordinates
              FONT_HERSHEY_COMPLEX_SMALL,  // Font
              1.0,                         // Scale. 2.0 = 2x bigger
              Scalar(255, 255, 255),       // BGR Color
              1,                           // Line Thickness (Optional)
              LINE_AA);                    // Anti-alias (Optional, see version note)
                                           // for( int i = 0; i< contours.size(); i++ )
      // {
      // Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
      // drawContours( drawing, contours_poly, (int)i, color );
      // rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2 );
      // circle( drawing, centers[i], (int)radius[i], color, 2 );

      // }
    }
  }
  imshow("Contours", drawing);
}
}  // namespace cv

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  // Draw an example circle on the video stream
  if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
    cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(0, 255, 0));
  tracking_ball(cv_ptr->image);
  // Update GUI Window
  cv::imshow(OPENCV_WINDOW, cv_ptr->image);
  cv::waitKey(3);
  // if(cv::waitKey(30) >= 0) break;
  // Output modified video stream
  // Convert this message to a ROS sensor_msgs::Image message.
  // image_pub_.publish(cv_ptr->toImageMsg());
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tennis_ball_listener_node");
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_(nh_);
  image_transport::Subscriber image_sub_;
  // Subscribe to input video feed and publish output video feed
  image_sub_ = it_.subscribe("tennis_ball_image", 1, imageCallback);

  ros::spin();
  // Close all the frames
  cv::destroyAllWindows();

  return 0;
}