#!/bin/bash

mkdir -p Debug
cd Debug

# Build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
