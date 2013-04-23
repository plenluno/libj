// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/symbol.h>

namespace libj {

Symbol::CPtr Symbol::create(const char* str) {
    return String::intern(str);
}

Symbol::CPtr Symbol::create(String::CPtr str) {
    return String::intern(str);
}

}  // namespace libj
