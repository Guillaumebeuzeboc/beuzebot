#!/bin/zsh

export ROS_MASTER_URI=http://192.168.178.4:11311
myip=$(ifconfig eth0 | grep 'inet addr:' | cut -d: -f2 | awk '{ print $1}')
export ROS_IP=${myip}
