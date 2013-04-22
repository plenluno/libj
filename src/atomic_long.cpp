// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/atomic_long.h>
#include <libj/detail/generic_atomic.h>

namespace libj {

AtomicLong::Ptr AtomicLong::create() {
    return Ptr(new detail::GenericAtomic<libj::AtomicLong, Long>(0));
}

AtomicLong::Ptr AtomicLong::create(Long val) {
    return Ptr(new detail::GenericAtomic<libj::AtomicLong, Long>(val));
}

}  // namespace libj
