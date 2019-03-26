#include <ros/ros.h>

//pager rings (prints "RING" to console) when its number is sent by queue

class Pager() {
private:

public:
  void initialize() {
    ros::Subscriber sub = n.subscribe("order_end", 1, &Pager::orderCompletedCallback, this);
  }

  //obtained from queue
  void orderCompletedCallback(int pager_number) {
  	ROS_INFO_STREAM("Pager RING id "<<pager_number);
  }
};



int main(int argc, char **argv)
{
  ros::init(argc, argv, "pager");
  ros::NodeHandle n;

  Pager pager;
  pager.initialize();

  ros::spin();

  return 0;
}