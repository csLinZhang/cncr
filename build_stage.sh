#!/bin/bash
set -ue
SIMULATION_ROOT=$(cd `dirname $0`; pwd)

cd ${SIMULATION_ROOT}/stage
mkdir build && cd build
cmake .. && sudo make install

cd ${SIMULATION_ROOT}