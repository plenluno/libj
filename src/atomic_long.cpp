// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/atomic_long.h>
#include <libj/detail/atomic.h>

namespace libj {

AtomicLong::Ptr AtomicLong::create() {
    return Ptr(new detail::Atomic<libj::AtomicLong, Long>(0));
}

AtomicLong::Ptr AtomicLong::create(Long val) {
    return Ptr(new detail::Atomic<libj::AtomicLong, Long>(val));
}

}  // namespace libj
