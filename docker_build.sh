#!/bin/bash
set -ue
CURRENT_PATH=$(cd `dirname $0`; pwd)
cd ${CURRENT_PATH}

HOST_ARCH=$(uname -m | grep -w -q 'x86_64' && echo 'amd64' || echo 'arm64')
IMAGE_NAME="simulation"
VERSION="v1.5"
TERGEO_VERSION="v1.5"
HUB_PATH="tonglu-docker.pkg.coding.net/simulation/simulation"

docker build --build-arg HOST_ARCH=${HOST_ARCH} --build-arg VERSION=${TERGEO_VERSION} -t ${IMAGE_NAME}_${HOST_ARCH}:${VERSION} .
