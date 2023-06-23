#ifndef ROSBAG_HEALTH_CHECK_NODE_HPP
#define ROSBAG_HEALTH_CHECK_NODE_HPP

#include <set>
#include <string>

#include <ros/ros.h>
#include <rosbag/view.h>

#include <XmlRpcValue.h>

namespace rosbag_health_check
{
  class BagChecker
  {
  public:
    ~BagChecker()
    {
      bag.close();
    }

    bool Open(std::string file_name);

    rosbag::Bag bag;
    std::shared_ptr<rosbag::View> view;
    rosbag::View::iterator iter;
    std::set<std::string> topics;
  };
}

#endif // ROSBAG_HEALTH_CHECK_NODE_HPP
