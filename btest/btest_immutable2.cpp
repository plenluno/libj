// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/mutable.h>

#include "./btest_immutable.h"

int main() {
    libj::BTestImmutable::CPtr p = libj::BTestImmutable::create();
    libj::Mutable::CPtr p2 = p;
}
