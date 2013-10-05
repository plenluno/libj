#!/bin/sh
mkdir -p build.ios
cd build.ios
cmake -DCMAKE_TOOLCHAIN_FILE=`dirname $0`/../tools/ios-cmake/toolchain/iOS.cmake -DCMAKE_BUILD_TYPE=Release -GXcode $@ ..
xcodebuild -configuration Release
