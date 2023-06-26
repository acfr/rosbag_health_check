#include "rosbag_health_check_node.hpp"

namespace rosbag_health_check
{
  bool BagChecker::Open(std::string file_name)
  {
    bag.open(file_name);

    if (!bag.isOpen())
    {
      ROS_INFO_STREAM("Could not OPEN bag file " << file_name);
      return false;
    }

    XmlRpc::XmlRpcValue my_list;
    ros::param::get("rosbag_health_check/topic_settings", my_list);

    rosbag::View connections_view(bag);
    for (const rosbag::ConnectionInfo *info : connections_view.getConnections())
    {
      for (int32_t i = 0; i < my_list.size(); ++i)
      {
        if (my_list[i].hasMember(info->topic))
        {
          std::string name = my_list[i][info->topic]["topic_name"];
          bool required_in_rosbag = my_list[i][info->topic]["required_in_rosbag"];
          bool required_frequency_check = my_list[i][info->topic]["required_frequency_check"];

          if (required_in_rosbag)
          {
            ROS_INFO_STREAM(name << " : Is an expected topic");
            if (required_frequency_check)
            {
              // check if the frequency of the topic from the bag matches the config settings
              double rate = my_list[i][info->topic]["rate"];

              // ROS_INFO_STREAM();
            }
            else
            {
              ROS_INFO_STREAM("Frequency Check not needed for " << name);
            }
          }
        }
        else
        {
          ROS_INFO_STREAM("Did not pass health check " << info->topic);
        }
      }
    }
    return true;
  }

}
int main(int argc, char *argv[])
{
  ros::init(argc, argv, "rosbag_health_check_node");
  // Create a private ROS node handle
  ros::NodeHandle nh;

  rosbag_health_check::BagChecker rosbag_check;

  // determine the bag file to playback
  std::string bag_file_name;
  nh.getParam("bag_file", bag_file_name);

  boost::filesystem::path canonicalPath = boost::filesystem::canonical(bag_file_name);
  bag_file_name = canonicalPath.string();

  if (bag_file_name.empty()) {
    ROS_INFO_STREAM("Bag file name parameter is missing " << bag_file_name);
    ros::shutdown();
  }

  if (!rosbag_check.Open(bag_file_name))
    ros::shutdown();

  ros::spin();
}