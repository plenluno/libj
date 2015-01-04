#!/bin/sh
# export ANDROID_NDK=/path/to/android-ndk
mkdir -p build.android
cd build.android
cmake -DCMAKE_TOOLCHAIN_FILE=`dirname $0`/android-cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9 -DANDROID_NATIVE_API_LEVEL=android-9 -DANDROID_ABI=armeabi $@ ..
make
