#include <iostream>

#include "opencv2/opencv.hpp"
//#include <string.h>

using namespace cv;

int main(int, char**)
{
  // VideoCapture video_capture(0); // open the default camera}
  VideoCapture vid("/home/javier/catkin_ws/src/udemy_ros_beginners/src/opencv_example/video/tennis-ball-video.mp4");
  // /home/javier/catkin_ws/src/udemy_ros_beginners/video/tennis-ball-video.mp4");

  if (!vid.isOpened())
  {  // check if we succeeded
    std::cout << "Error opening video stram or file" << std::endl;
    return -1;
  }

  while (1)
  {
    Mat frame;
    Mat hsv_frame;
    Mat maskHSV, resultHSV;

    // Capture frame-by-frame
    vid >> frame;
    // if the frame is empty, breake
    if (frame.empty())
      break;
    // Display the resulting frame
    imshow("Frame RAW", frame);

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

    // *******************************************************************************

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