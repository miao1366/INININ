FROM ubuntu:18.04

# Install necessary packages for the installer
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake pkg-config wget tar \
    libjpeg-dev libpng-dev libtiff-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev \
    libgtk-3-dev \
    libatlas-base-dev gfortran \
    python3-dev \
    libc-ares-dev \
    libc-ares-dev uuid-dev libssl-dev \
    autoconf automake libtool \
    libcrypto++* \
    libprotobuf-dev libleveldb-dev libsnappy-dev libhdf5-serial-dev \
    libboost-all-dev libopenblas-dev liblapack-dev libatlas-base-dev \
    libgflags-dev libgoogle-glog-dev liblmdb-dev \
    protobuf-c-compiler protobuf-compiler libprotobuf-dev libprotobuf-c-dev libprotoc-dev \
    liblmdb-dev libleveldb-dev libhdf5-serial-dev \
    libgstreamer-plugins-base1.0-dev \
    libavresample-dev libwebsockets-dev libcurl4-openssl-dev bash-completion\
    && apt-get clean

RUN mkdir -p /tmp/build_opencv/ \
    && wget ftp://192.168.0.7/Pub/HornedSungem/Docker/build_opencv3.4.5_20190320.tar.bz -O /tmp/build_opencv/build_opencv3.4.5_20190320.tar.bz \
    && tar -xjf /tmp/build_opencv/build_opencv3.4.5_20190320.tar.bz -C /tmp/build_opencv/ \
    && make -C /tmp/build_opencv/opencv-3.4.5/build install \
    && ldconfig \
    && rm -rf /tmp/build_opencv

# libssl-dev ==> libssl1.0-dev
# install software-properties-common
# cmake: https://launchpad.net/~rsjtaylor/+archive/ubuntu/cmake-backports 3.10.2-1ubuntu2 ==> 3.12.3-3~ubuntu18.04.1~ppa1

# eclipse-mosquitto docker
# https://hub.docker.com/_/eclipse-mosquitto?tab=description

# mysql docker
# https://hub.docker.com/_/mysql?tab=description
# https://hub.docker.com/r/mysql/mysql-server

# postgresql docker
# https://hub.docker.com/_/postgres

# mosquitto用1.5.8版本源码编译安装
# libwebsockets-dev用apt-get装
# run docker
# sudo docker run --net=host --privileged --name develop_self_fms_env_v1.2 -v /dev:/dev -v /home/rain/DockerAll/policy_server/developSelfFms/:/home/senscape/project_run/ -i -t develop_self_fms:v1.2 bash
# cmake -DENABLE_RECOGNISE=OFF ..
