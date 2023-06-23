FROM ros:melodic-perception-bionic

RUN apt-get update && apt-get install -y ros-melodic-random-numbers ffmpeg vim python-catkin-tools ros-melodic-rqt-bag python-pip python-tk 

RUN mkdir -p /catkin/src && \
    catkin init -w /catkin && \
    /bin/sh /opt/ros/melodic/setup.sh && \
    git clone -c http.sslverify=false -b git@github.com:acfr/rosbag_health_check.git /catkin/src/rosbag_health_check && \
    cd /catkin/src/rosbag_health_check && \
    git submodule init && \
    git -c http.sslverify=false submodule update 

RUN  rosdep install --from-paths /catkin/src/rosbag_health_check --ignore-src -y

RUN /bin/bash -c "source /opt/ros/melodic/setup.bash; cd /catkin; catkin build;"

RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
RUN echo "source /catkin/devel/setup.bash" >> ~/.bashrc

