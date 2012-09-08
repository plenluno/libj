// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/value.h>

int main() {
    libj::Value v = 5;
    libj::Value* vp = &v;
    int* ip;
    libj::to<const int>(vp, &ip);
    
    return 0;
}
