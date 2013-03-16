// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_ATOMIC_LONG_H_
#define LIBJ_ATOMIC_LONG_H_

#include <libj/mutable.h>

namespace libj {

class AtomicLong : LIBJ_MUTABLE(AtomicLong)
 public:
    static Ptr create();

    static Ptr create(Long initVal);

    virtual Long get() const = 0;

    virtual Long addAndGet(Long delta) = 0;

    virtual Long incrementAndGet() = 0;

    virtual Long decrementAndGet() = 0;

    virtual void set(Long newVal) = 0;
};

}  // namespace libj

#endif  // LIBJ_ATOMIC_LONG_H_
