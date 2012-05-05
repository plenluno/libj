// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/console.h"
#include "libj/json.h"
#include "libj/string.h"

#include <iostream>

namespace libj {
namespace console {

void log(Value val) {
    Type<String>::Cptr s;
    if (val.instanceOf(Type<String>::id())) {
        s = toCptr<String>(val);
    } else {
        s = json::stringify(val);
    }
    for (Size i = 0; i < s->length(); i++) {
        std::cout << static_cast<char>(s->charAt(i));
    }
    std::cout << std::endl;
}

}  // namespace console
}  // namespace libj
