#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

using namespace cv;
using namespace std;

 
int main( )
{
 
       Mat image;
 
       // LOAD image
       // Read the file "image.jpg":
       image = imread("/home/javier/catkin_ws/src/udemy_ros_beginners/src/opencv_example/images/chess.jpg",cv::IMREAD_COLOR);
              //This file "image.jpg" should be in the project folder.
              //Else provide full address : "D:/images/image.jpg"
 
       if(! image.data )  // Check for invalid input
       {
              cout <<  "Could not open or find the image" << std::endl ;
              return -1;
       }
 
       //DISPLAY image
       namedWindow( "window", WINDOW_AUTOSIZE ); // Create a window for display.
       imshow( "window", image ); // Show our image inside it.
 
       //SAVE image
       imwrite("/home/javier/catkin_ws/src/udemy_ros_beginners/src/opencv_example/images/copy/copy_image.jpg",image);// it will store the image in name "result.jpg"
 
       waitKey(0);                       // Wait for a keystroke in the window
       return 0;
}
