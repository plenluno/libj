// Copyright (c) 2012 Plenluno All rights reserved.

#include <cassert>
#include <exception>

namespace boost {

void throw_exception(const std::exception&) {
    assert(0);
}

}  // namespace boost
