#!/bin/bash

set -ue
CURRENT_PATH=$(cd `dirname $0`; pwd)
cd ${CURRENT_PATH}

../app/tergeo_multi --start ../conf/modules/multi_module.conf
