#!/bin/bash

set -ue
CURRENT_PATH=$(cd `dirname $0`; pwd)
cd ${CURRENT_PATH}

../app/tergeo --start ../conf/modules/vehicle_module.conf
