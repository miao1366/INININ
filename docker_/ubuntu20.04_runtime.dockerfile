FROM ubuntu:18.04

ENV  TIME_ZONE Asiz/Shanghai
RUN set -x && \
    apt-get update && \
    apt-get install -y software-properties-common && \
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
    libglib2.0-0 \
    libmosquittopp1 \
    libboost-all-dev \
    libssl1.1 \
    libcrypto++6 \
    libcurl4 \
    libgoogle-glog0v5 \
    uuid-runtime \
    libopencv-dev \
    libzmqpp4 \
    libwebsocketpp-dev \
    libcpprest2.10 \
    libsqlite3-0 \
    sqlite3
