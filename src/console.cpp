// Copyright (c) 2012 Plenluno All rights reserved.

#include <iostream>

#include "libj/collection.h"
#include "libj/console.h"
#include "libj/json.h"
#include "libj/map.h"
#include "libj/string.h"

namespace libj {
namespace console {

Boolean log(const Value& val) {
    String::CPtr s = String::null();
    if (val.instanceof(Type<Map>::id()) ||
        val.instanceof(Type<Collection>::id())) {
        s = json::stringify(val);
    } else {
        s = String::valueOf(val);
    }
    if (s) {
        std::cout << s->toStdString() << std::endl;
        return true;
    } else {
        return false;
    }
}

}  // namespace console
}  // namespace libj
