#!/bin/bash
XSOCK=/tmp/.X11-unix
XAUTH=$HOME/.Xauthority
VOLUMES="--volume=${PWD}/../rosbag_health_check:/catkin/src/rosbag_health_check:rw"

xhost +local:docker

docker run \
-it --rm \
-v /media:/media/jerome/Samsung_T5/ \
$VOLUMES \
$ENVS \
--privileged \
--net=host \
--workdir="/catkin" \
--name rosbag_health_check 