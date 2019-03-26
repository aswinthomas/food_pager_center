#include <ros/ros.h>
#include <queue>

// queue stores order numbers and their assigned pager numbers'
class Queue {
private:
  unordered_map<int,int> orders;
  ros::Publisher pub_pager;

public:

  void initialize() {
  	ros::Subscriber sub1 = n.subscribe("order_start", 1, &Chef::orderStartCallback, this);
  	ros::Subscriber sub2 = n.subscribe("cooking_complete", 1, &Queue::cookingEndCallback, this);

  	pub_order_complete_ = n.advertise<int>("cooking_complete", 1);
  }

  //obtained from cashier
  void orderStartCallback(Order order) {
  	orders[order.number] = order.pager;
  }

  //obtained from chef
  void cookingEndCallback(Order order) {
  	//send to pager
  	pub_pager.publish(order.pager);
  	orders.erase(order.number);
  }
};




int main(int argc, char **argv)
{
  ros::init(argc, argv, "queue");
  ros::NodeHandle n;

  Queue queue;
  queue.initialize();
  for(int i=5000; i<5005; i++) cashier.addPager(i);

  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    char c = getch();
    if(c=='r' || c=='R') cashier.generateOrder();
    loop_rate.sleep();
    ros::spinOnce();
  }


  return 0;
}