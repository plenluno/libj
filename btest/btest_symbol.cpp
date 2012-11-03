// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/symbol.h>

int main() {
    libj::Symbol::CPtr symbol = libj::Symbol::create("abc");
    symbol = libj::Symbol::create("123");

    return 0;
}
