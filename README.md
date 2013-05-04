libj
====

libj is a cross-platform native runtime library equipped with Java/JavaScript-like API.

### Build

    git clone --recursive https://github.com/plenluno/libj.git
    mkdir libj/build
    cd libj/build
    cmake ..
    make

The memory management of libj is automatic, based on either shared_ptr or bdw-gc.  
libj uses shared_ptr by default. In order to use bdw-gc,  

    cmake -DLIBJ_USE_BDWGC=ON ..

If your compiler supports C++11,

    cmake -DLIBJ_USE_CXX11=ON ..

The following option allows you to use thread-related classes and concurrent collection classes.

    cmake -DLIBJ_USE_THREAD=ON ..
