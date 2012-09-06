// Copyright (c) 2012 Plenluno All rights reserved.

#include "./btest_mutable.h"

int main() {
    // noncopyable
    libj::BTestMutable x, y = x;
}
