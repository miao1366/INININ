FROM ubuntu:18.04
# Install necessary packages for the installer
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake pkg-config \
    wget \
    tar \
    libglib2.0-0 \
    sed \
    tar \
    bash-completion \
    libcurl4-openssl-dev \
    libboost-regex1.65.1 \
    libgoogle-glog0v5 \
    libcrypto++6 \
    libboost-thread1.65.1 \
    libprotobuf10 \
    libhdf5-100 \
    liblmdb0 \
    libleveldb1v5 \
    libatlas3-base \
    libopenblas-base \
    libjpeg8 \
    libpng16-16 \
    libtiff5 \
    libgtk-3-0 \
    libgstreamer-plugins-base1.0-0 \
    libavcodec57 \
    libavformat57 \
    libswscale4 \
    libboost-filesystem1.65.1 \
    libwebsockets8 \
    nginx \
    && apt-get clean \
    && mkdir -p /tmp/install_opencv/ \
    && wget ftp://192.168.0.7/Pub/HornedSungem/Docker/libopencv-3.4.5packages20190320.tar.bz -O /tmp/install_opencv/libopencv-3.4.5packages20190320.tar.bz \
    && tar -xjf /tmp/install_opencv/libopencv-3.4.5packages20190320.tar.bz -C /tmp/install_opencv/ \
    && mv /tmp/install_opencv/libopencv-3.4.5packages/usr/local/lib/* /usr/local/lib/ \
    && ldconfig \
    && rm -rf /tmp/install_opencv \
	&& mkdir -p /home/senscape/project_run \
    && mkdir -p /home/senscape/project_run/env \
    && mkdir -p /etc/nginx/sites-enabled/
#mosquito
COPY ./release/mosquitto-1.5.8 /home/senscape/project_run/tmp/
#网页
# COPY ./release/nginx/nginx.conf /etc/niginx/
COPY ./release/nginx/default /etc/nginx/sites-enabled/
# ADD ./release/html.tar.gz /home/senscape/Public/
RUN cd /home/senscape/project_run/tmp/ && make install && rm -rf /home/senscape/project_run/tmp

# COPY ./release/models/* /home/senscape/project_run/models/
# COPY ./release/model_256/* /home/senscape/project_run/model_256/
# COPY ./release/runtime_lib/* /usr/local/lib/
# COPY ./release/run_fms_master.sh /home/senscape/project_run/
# COPY ./release/fms_master /home/senscape/project_run/


WORKDIR /home/senscape/project_run
#调试版
#sudo docker run --net=bridge --privileged --name mult_policy_server1 -v /dev/:/dev/ -v /home/rain/DockerAll/policy_server/multSelfFms/policy_server1/:/home/senscape/project_run/ -p 40000:1882 -p 40001:80 -p 40002:11883  -i -t mult_self_fms:v1.2 bash
#正式版
#sudo docker run --net=bridge --restart=always --privileged --name mult_policy_server1 -v /dev/:/dev/ -v /home/rain/DockerAll/policy_server/multSelfFms/policy_server1/:/home/senscape/project_run/ -p 40000:1882 -p 40001:80 -p 40002:11883  -i -t mult_self_fms:v1.2 ./run_fms_master.sh
