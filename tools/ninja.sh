#!/bin/sh
mkdir -p build
cd build
cmake -G Ninja $@ ..
ninja
