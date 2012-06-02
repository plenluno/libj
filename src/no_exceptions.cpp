// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_USE_EXCEPTION

#include <cassert>
#include <exception>

namespace boost {

void throw_exception(const std::exception&) {
    assert(0);
}

}  // namespace boost

#endif  // LIBJ_USE_EXCEPTION
