// Copyright (c) 2012 Plenluno All rights reserved.

#include "./btest_immutable.h"

int main() {
    // noncopyable
    libj::BTestImmutable x, y;
    x = y;
}
