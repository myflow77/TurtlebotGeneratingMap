#include "header.h"

int turtlebotMove()
{
  geometry_msgs::Twist geo_msg;

  if(depthCheck_depth())  //장애물 있을 때.
  {
    nav_msgs::Odometry msg;
    double goalangle;

    goalangle = dothisAngle();

	geo_msg.linear.x = 0;
	geo_msg.angular.z = 0;
  	g_pubGeo.publish(geo_msg);

	calcDistance();

    while(1)
    {
      mutex[0].lock(); {
         msg = g_odom;
      } mutex[0].unlock();

      double angle = atan2((2*msg.pose.pose.orientation.w*msg.pose.pose.orientation.z),(1-2*msg.pose.pose.orientation.z*msg.pose.pose.orientation.z));



      //std::cout << angle << ", " << goalangle << std::endl;

      if(angle<=goalangle + 0.1 &&angle>= goalangle - 0.1)
      {
        break;
      }

      if(angle>goalangle)
      {
  		  geo_msg.linear.x = 0;
  		  geo_msg.angular.z = -1*0.5;
        g_pubGeo.publish(geo_msg);
      }
      else if(angle<goalangle)
      {
        geo_msg.linear.x = 0;
  		  geo_msg.angular.z = 0.5;
        g_pubGeo.publish(geo_msg);
      }

    }
  }
  else  //장애물 없을 때.
  {
	  std::cout << "Start Straight!!!!!!!!!!!!" << endl;
    geo_msg.linear.x = 0.2;
    geo_msg.angular.z = 0;
    g_pubGeo.publish(geo_msg);
  }

  return 0;
}
