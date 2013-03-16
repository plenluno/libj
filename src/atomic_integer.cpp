// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/atomic_integer.h>
#include <libj/detail/atomic.h>

namespace libj {

AtomicInteger::Ptr AtomicInteger::create() {
    return Ptr(new detail::Atomic<libj::AtomicInteger, Int>(0));
}

AtomicInteger::Ptr AtomicInteger::create(Int val) {
    return Ptr(new detail::Atomic<libj::AtomicInteger, Int>(val));
}

}  // namespace libj
