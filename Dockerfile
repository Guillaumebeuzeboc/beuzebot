# Set the base image
FROM ros:indigo-ros-core

MAINTAINER guillaume beuzeboc <guillaume.beuzeboc@gmail.com> 


RUN apt-get update
RUN apt-get install -y wget \
                       g++ \
                       cmake \
                       unzip \
                       libgflags-dev

RUN apt-get install -y ros-indigo-hardware-interface \
                       ros-indigo-controller-manager \
                       ros-indigo-control-msgs \
                       ros-indigo-actionlib \
                       ros-indigo-urdf \
                       ros-indigo-joint-limits-interface \
                       ros-indigo-transmission-interface \
                       ros-indigo-control-toolbox \
                       ros-indigo-angles \
                       ros-indigo-rosparam-shortcuts

# install pigpio
RUN wget -P /tmp/ abyz.co.uk/rpi/pigpio/pigpio.zip
RUN cd /tmp; unzip pigpio.zip
RUN cd /tmp/PIGPIO; make; make install

#depends ws
RUN mkdir -p /root/ros_depends/src
RUN git clone --branch 0.4.1 https://github.com/Guillaumebeuzeboc/ros_control_boilerplate.git /root/ros_depends/src/ros_control_boilerplate
RUN /bin/bash -c "source /opt/ros/indigo/setup.bash; cd /root/ros_depends; catkin_make install"

#install ws
RUN mkdir -p /root/ws/src
RUN /bin/bash -c "source /opt/ros/indigo/setup.bash; cd /root/ws; catkin_make"

# Copy and run code
COPY src/ /root/ws/src
