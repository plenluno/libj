libj
====

[![Build Status](https://travis-ci.org/plenluno/libj.png?branch=master)](https://travis-ci.org/plenluno/libj)

libj is a cross-platform native runtime library equipped with Java/JavaScript-like API
and enables you to write efficient C++ code in a similar way to Java/JavaScript.

### Source Code

You need to clone all the dependant submodules to build libj.

    git clone --recursive https://github.com/plenluno/libj.git

### Build

##### Linux/Mac

    mkdir libj/build
    cd libj/build
    cmake ..
    make

The memory management of libj is automatic, based on either shared_ptr or bdw-gc.  
libj uses shared_ptr by default. In order to use bdw-gc,  

    cmake -DLIBJ_USE_BDWGC=ON ..

The following option allows you to use thread-related classes and concurrent collection classes.

    cmake -DLIBJ_USE_THREAD=ON ..

##### Windows

    tools/windows-cmake.ps1 [cmake-option ...]

##### Android

    export ANDROID_NDK=/path/to/android-ndk
    tools/android-cmake.sh [cmake-option ...]

##### iOS

    tools/ios-cmake.sh [cmake-option ...]
