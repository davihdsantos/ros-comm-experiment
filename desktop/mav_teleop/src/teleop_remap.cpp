//=================================================================================================
// Copyright (c) 2012-2016, Institute of Flight Systems and Automatic Control,
// Technische Universität Darmstadt.
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of hector_quadrotor nor the names of its contributors
//       may be used to endorse or promote products derived from this software
//       without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/JointState.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <string>
#include <stdint.h>

namespace teleop_remap
{

class Teleop
{
private:

  ros::NodeHandle node_handle_;
  ros::Subscriber remote_subscriber_;
  ros::Publisher local_publisher_;

public:
  Teleop()
  {
    ros::NodeHandle private_nh("~");

    remote_subscriber_ = node_handle_.subscribe<std_msgs::Float64>("/remote/mavros/rc/override", 1,
                                                               boost::bind(&Teleop::joyAttitudeCallback, this, _1));

    local_publisher_ = node_handle_.advertise<mavros_msgs::OverrideRCIn>(
        "/mavros/rc/override", 1);
  }

  ~Teleop()
  {
    stop();
  }

  void joyAttitudeCallback(const std_msgs::Float64::ConstPtr &joy)
  {
    mavros_msgs::OverrideRCIn rudder_cmd;

    rudder_cmd.channels[0] = (uint16_t)joy->data;
    rudder_cmd.channels[2] = (uint16_t)1100;

    local_publisher_.publish(rudder_cmd);
  }

  void stop()
  {
    if (local_publisher_.getNumSubscribers() > 0) 
    {
      local_publisher_.publish(mavros_msgs::OverrideRCIn());
    }
  }
};

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "teleop_remap");

  teleop_remap::Teleop teleop;
  ros::spin();

  return 0;
}