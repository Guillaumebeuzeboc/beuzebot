current_dir = $(shell pwd)
all:
	docker build -f Dockerfile -t guillaumebeuzeboc/beuzebot .
run_docker:
	docker run -it -v ${current_dir}/src:/root/ws/src guillaumebeuzeboc/beuzebot bash
build_code:
	docker run guillaumebeuzeboc/beuzebot /bin/bash -c "source /opt/ros/indigo/setup.bash; source /root/ros_depends/install/setup.bash; cd /root/ws; catkin_make"
