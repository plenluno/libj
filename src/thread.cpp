// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/detail/thread.h>

namespace libj {

Thread::Ptr Thread::create(Function::Ptr func) {
    if (func) {
        return Ptr(new detail::Thread(func));
    } else {
        return null();
    }
}

}  // namespace libj
