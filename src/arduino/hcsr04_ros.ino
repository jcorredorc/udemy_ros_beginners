
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <HCSR04.h>

ros::NodeHandle nh;
HCSR04 hc(2, 3);  // initialisation class HCSR04 (trig pin , echo pin)

sensor_msgs::Range range_msg;
ros::Publisher pub_range("/ultrasound_range", &range_msg);
char frameid[] = "/ultrasound";

void setup()
{
  // initialize serial communication:
  nh.initNode();
  nh.advertise(pub_range);

  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id = frameid;
  range_msg.field_of_view = 0.2618;  // 15 degrees
  range_msg.min_range = 0.02;        // 2 cm
  range_msg.max_range = 4;           // 400 cm

  // Serial.begin(9600);
}

void loop()
{
  range_msg.range = hc.dist() / 100;  // getRange in [m]
  range_msg.header.stamp = nh.now();
  pub_range.publish(&range_msg);
  nh.spinOnce();
  delay(60);
}