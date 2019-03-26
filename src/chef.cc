#include <ros/ros.h>
#include <queue>


//chef inputs a completed order number and sends it to queue

class Chef {
  private:
  	std::queue<int> order_q_;
  	bool cooking;
  	ros::Publisher pub_order_complete_;

  public:
  	Chef(): cooking(false) { }

  	void initialize() {
  		ros::Subscriber sub = n.subscribe("order_start", 1, &Chef::orderStartCallback, this);
  		pub_order_complete_ = n.advertise<int>("cooking_complete", 1);
  	}

  	//obtained from cashier
    void orderStartCallback(Order order) {
      order_q_.push(order.number);
    }

    void cook() {
      if(order_q_.empty()) return;
      double prev_time = ros::Time::now().toSec();
      double curr_time = ros::Time::now().toSec();
      int order = order_q_.front();

      while(fabs(curr_time-prev_time)<COOKING_TIME) {
      	curr_time = ros::Time::now().toSec();
      	sleep(1);
      	ROS_INFO("")
      }

      pub_order_complete_.publish(order);
      order_q_.pop();
    }
}



int main() {
	Chef chef;

	loop_rate(1);

	while(ros::ok()) {
	  chef.cook();
	  loop_rate.sleep();
	  ros::spinOnce();
	}
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "pager");
  ros::NodeHandle n;

  Chef chef;
  chef.initialize();

  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    chef.cook();
	  loop_rate.sleep();
	  ros::spinOnce();
  }


  return 0;
}