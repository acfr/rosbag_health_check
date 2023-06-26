FROM ros:melodic-perception-bionic

RUN apt-get update && apt-get install -y ros-melodic-random-numbers ffmpeg vim python-catkin-tools ros-melodic-rqt-bag python-pip python-tk 

RUN mkdir -p ~/catkin/src && \
    catkin init -w ~/catkin && \
    git clone https://github.com/acfr/rosbag_health_check.git ~/catkin/src/rosbag_health_check 

RUN  rosdep install --from-paths ~/catkin/src/rosbag_health_check --ignore-src -y

RUN /bin/bash -c "source /opt/ros/melodic/setup.bash; cd ~/catkin; catkin build;"

RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
RUN echo "source /catkin/devel/setup.bash" >> ~/.bashrc

