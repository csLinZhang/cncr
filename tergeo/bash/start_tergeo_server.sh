#!/bin/bash

set -ue
CURRENT_PATH=$(cd `dirname $0`; pwd)
cd ${CURRENT_PATH}

../app/tergeo_qt_core --start ../conf/modules/tergeo_server_module.conf
