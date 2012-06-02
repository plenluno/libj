// Copyright (c) 2012 Plenluno All rights reserved.

#include <iostream>

#include "libj/console.h"
#include "libj/json.h"
#include "libj/string.h"

namespace libj {
namespace console {

Boolean log(const Value& val) {
    String::CPtr s = String::valueOf(val);
    if (!s)
        return false;
    std::cout << s->toStdString() << std::endl;
    return true;
}

}  // namespace console
}  // namespace libj
