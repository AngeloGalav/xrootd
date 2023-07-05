#!/bin/bash
apt -y update
apt -y install \
    cmake \
    davix-dev \
    g++ \
    libcppunit-dev \
    libcurl4-openssl-dev \
    libfuse-dev \
    libgtest-dev \
    libisal-dev \
    libjson-c-dev \
    libkrb5-dev \
    libmacaroons-dev \
    libreadline-dev \
    libscitokens-dev \
    libssl-dev \
    libsystemd-dev \
    libtinyxml-dev \
    libxml2-dev \
    make \
    pkg-config \
    python3-dev \
    python3-setuptools \
    uuid-dev \
    voms-dev \
    zlib1g-dev

apt -y install git