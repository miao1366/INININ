FROM ubuntu:latest

ENV  TIME_ZONE Asiz/Shanghai
RUN set -x && \
    apt-get update && \
    apt-get install -y software-properties-common && \
    apt-add-repository ppa:mosquitto-dev/mosquitto-ppa && \
    apt-get update && \
    apt-get install tzdata && \
    echo "${TIME_ZONE}" > /etc/timezone && \
    ln -sf /usr/share/zoneinfo/${TIME_ZONE} /etc/localtime && \
    apt-get install -y \
    build-essential \
    cmake pkg-config \
    wget \
    tar \
    vim \
    git \
    libglib2.0-dev \
    libmosquitto-dev \
    libboost-all-dev \
    libssl-dev \
    libcrypto++-dev \
    libcurl4-openssl-dev \
    libgoogle-glog-dev \
    uuid-dev \
    libopencv-dev