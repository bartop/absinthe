#!/bin/bash

set -e

conan install -if .module-path .
cmake -S . -B .build -DCMAKE_MODULE_PATH=.module-path

make all -C .build -j8
make test -C .build -j8
