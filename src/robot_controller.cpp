#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include <sstream>



ros::Publisher *p_pub;


/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void twistCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  p_pub->publish(msg);
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
 
}


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "cmd_vel");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  // Create a float variable to hold the parameter
  // This time initialize it to a default value
  double wall_dist = 1.0;
  // Announce the value of wall_dist before the first call to the Parameter Server
  ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);
  


  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  p_pub = &cmd_vel_pub;


  ros::Subscriber twist_sub = n.subscribe("des_vel", 1000, twistCallback);
  ros::Subscriber laser_sub = n.subscribe("lidar_1", 1000, laserCallback);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    geometry_msgs::Twist msg;

    

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    cmd_vel_pub.publish(msg);

    // Get the parameter using the node handle that can be updated
    // Removed & sign!!!!!
    if (n.getParamCached("wall_dist", wall_dist)) {
      ROS_INFO("wall_dist was updated to: [%2.2f]", wall_dist);
    }

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}