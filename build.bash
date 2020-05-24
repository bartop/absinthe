#!/bin/bash

set -e

if [ ! -d build ]
then
    mkdir -p build
    cd build
    cmake ..
    cd ..
fi

cd build

make -j4
make test
