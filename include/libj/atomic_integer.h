// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_ATOMIC_INTEGER_H_
#define LIBJ_ATOMIC_INTEGER_H_

#include <libj/mutable.h>

namespace libj {

class AtomicInteger : LIBJ_MUTABLE(AtomicInteger)
 public:
    static Ptr create();

    static Ptr create(Int initVal);

    virtual Int get() const = 0;

    virtual Int addAndGet(Int delta) = 0;

    virtual Int incrementAndGet() = 0;

    virtual Int decrementAndGet() = 0;

    virtual void set(Int newVal) = 0;
};

}  // namespace libj

#endif  // LIBJ_ATOMIC_INTEGER_H_
