# Setup

## Xavier

### Requirements

- [Ubuntu 18.04](https://ubuntu.com/tutorials/install-ubuntu-desktop-1804#1-overview)
- [Xavier initial setup](https://www.youtube.com/watch?v=-nX8eD7FusQ)
- [ROS melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)
- [Zed setup](https://www.stereolabs.com/docs/ros/)
- ZED camera
- Setting up a static IP for the xavier helps

> **Note**: 

### Commands

        export ROS_IP=$XAVIER_LOCAL_IP
        source /opt/ros/melodic/setup.bash
        roslaunch zed_display_rviz display_zed.launch

> **Note**:  Use `ifconfig` to get the $XAVIER_IP (Ex: 192.168.1.10).

## Raspberry pi 4

### Requirements

- Pixhawk
- [Emlid Raspberry PI OS Buster](https://docs.emlid.com/navio2/configuring-raspberry-pi/)
- [MAVROS](https://docs.px4.io/v1.12/en/ros/mavros_installation.html)
- Setting up a [static IP for the Raspberry PI 4](https://www.makeuseof.com/raspberry-pi-set-static-ip/) helps

### Commands

        export ROS_IP=$RASPBERRY_IP
        export ROS_MASTER_URI=http://$XAVIER_IP:11311
        source ~/catkin_mavros/devel/setup.bash
        roslaunch mavros_teleop teleop_mavros.launch

## Desktop

### Requirements

- [Ubuntu 18.04](https://ubuntu.com/tutorials/install-ubuntu-desktop-1804#1-overview)
- [ROS melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)
- [MAVROS](https://docs.px4.io/v1.12/en/ros/mavros_installation.html)
- A joystick

### Commands

        export ROS_IP=$DESKTOP_IP
        export ROS_MASTER_URI=http://$XAVIER_IP:11311
        source ~/pi_ws/devel/setup.bash
        roslaunch mav_teleop sony_dualshock3.launch

> **Note**: make sure the joystick is connected and the analog light is on

## Notebook

### Requirements

- [Ubuntu 16.04](https://ubuntu.com/tutorials/install-ubuntu-desktop-1804#1-overview). It can be other versions of Ubuntu, 16.04 was the one I used for the experiment.
- [ROS kinetic](http://wiki.ros.org/kinetic/Installation/Ubuntu)
- Enable port forwarding in your gateway router. It should forward from `$GATEWAY_EXTERNAL_IP:X` (example X=50000) to `$XAVIER_IP:11311` (ip/port of master node).

> **Note**: [this website](https://whatismyipaddress.com/) shows your external ip

> **Note**: use [this website](https://www.canyouseeme.org/) to test the port forwarding

### Commands

        export ROS_IP=$DESKTOP_IP
        export ROS_MASTER_URI=http://$XAVIER_IP:11311
        rostopic list

> **Note**: most routers don't support loopback. This means you can't use your own external ip inside your local network. The notebook must be in another network (4G, another router, etc)