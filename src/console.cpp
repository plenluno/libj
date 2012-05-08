// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/console.h"
#include "libj/json.h"
#include "libj/string.h"

#include <iostream>

namespace libj {
namespace console {

bool log(const Value& val) {
    Type<String>::Cptr s = String::valueOf(val);
    if (!s)
        return false;
    for (Size i = 0; i < s->length(); i++) {
        std::cout << static_cast<char>(s->charAt(i));
    }
    std::cout << std::endl;
    return true;
}

}  // namespace console
}  // namespace libj
