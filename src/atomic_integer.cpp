// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/atomic_integer.h>
#include <libj/detail/generic_atomic.h>

namespace libj {

AtomicInteger::Ptr AtomicInteger::create() {
    return Ptr(new detail::GenericAtomic<libj::AtomicInteger, Int>(0));
}

AtomicInteger::Ptr AtomicInteger::create(Int val) {
    return Ptr(new detail::GenericAtomic<libj::AtomicInteger, Int>(val));
}

}  // namespace libj
