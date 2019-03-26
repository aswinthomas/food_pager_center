
// cashier inputs an (order number, pager number) pair and sends them to queue
#include <termios.h>
#include <ros/ros.h>


int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering      
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

  int c = getchar();  // read character (non-blocking)

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}

class Cashier {
  private:
    ros::Publisher pub_order_;
    vector<int> pagers_;
  	int order_number_;

  public:
  	Cashier() {}

  	void initialize() {
       pub_order_ = n.advertise<food_pager_center::Order>("order_start", 1);
  	}
  	
  	void addPager(int pager) {
	    pagers_.push_back(pager);
  	}

  	void generateOrder() {
  	  if(pagers_.empty()) {
        ROS_INFO("Unable to generate order since no pagers available");
        return;
      }

  	  order_number_++;
      Order order;
      order.number = order_number_;
      order.pager = pagers_[0];
      pagers_.erase(pagers.begin());
      pub_order_.publish(order);
  	}

    void order_completed_callback(Order order) {
      pagers_.push_back(order.pager);
    }
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "pager");
  ros::NodeHandle n;

  Cashier cashier;
  cashier.initialize();
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