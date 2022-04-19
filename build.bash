#!/bin/bash

set -e

PROCESSOR_COUNT=`nproc`

conan install --install-folder .module-path .
cmake -S . -B .build -DCMAKE_MODULE_PATH=.module-path

cmake --build .build -j${PROCESSOR_COUNT}
cmake --build .build -j${PROCESSOR_COUNT} --target test
