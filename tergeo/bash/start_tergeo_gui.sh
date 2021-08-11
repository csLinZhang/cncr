#!/bin/bash

set -ue
CURRENT_PATH=$(cd `dirname $0`; pwd)
cd ${CURRENT_PATH}

../app/tergeo_gui --start ../conf/modules/tergeo_gui_module.conf
