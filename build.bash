#!/bin/bash

set -e

if [ ! -d .build ]
then
    mkdir -p .build
    cd .build
    conan install ..
    cmake ..
    cd ..
fi

cd .build

make
make test
