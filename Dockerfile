# Set the base image
FROM ros:indigo-ros-core

MAINTAINER guillaume beuzeboc <guillaume.beuzeboc@gmail.com> 


RUN apt-get update
RUN apt-get install -y wget \
                       g++ \
                       cmake \
                       unzip

# install pigpio
RUN wget -P /tmp/ abyz.co.uk/rpi/pigpio/pigpio.zip
RUN cd /tmp; unzip pigpio.zip
RUN cd /tmp/PIGPIO; make; make install


#install ws
RUN mkdir -p /root/ws/src
RUN /bin/bash -c "source /opt/ros/indigo/setup.bash; cd /root/ws; catkin_make"

# Copy and run code
COPY src/ /root/ws/src
