#!/bin/zsh
robot_ip=$(nmap -sP "192.168.43.0/24" | grep beuzebot -A1 | awk '/is up/ {print up}; {gsub (/\(|\)/,""); up = $NF}')

export ROS_MASTER_URI=http://${robot_ip}:11311
myip=$(ifconfig wlp4s0 | grep 'inet addr:' | cut -d: -f2 | awk '{ print $1}')
export ROS_IP=${myip}
