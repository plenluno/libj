// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/value.h>

int main() {
    libj::Value v = 3;
    const libj::Value* vp = &v;
    int* ip;
    libj::to<int>(vp, &ip);

    return 0;
}
