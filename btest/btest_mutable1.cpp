// Copyright (c) 2012 Plenluno All rights reserved.

#include "./btest_mutable.h"

int main() {
    libj::BTestMutable::Ptr p = libj::BTestMutable::create();
    libj::Immutable::CPtr p2 = p;
}
