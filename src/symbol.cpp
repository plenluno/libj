// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/symbol.h>

namespace libj {

Symbol::CPtr Symbol::create(const char* str) {
    return String::intern(str);
}

}  // namespace libj
