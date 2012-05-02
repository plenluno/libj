// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_COLLECTION_H_
#define LIBJ_COLLECTION_H_

#include "libj/mutable.h"

namespace libj {

class Collection : LIBJ_MUTABLE(Collection)
 public:
    virtual Size size() const = 0;
    virtual bool add(Value) = 0;
    virtual void clear() = 0;
    // and so on
};

#define LIBJ_COLLECTION(T) public libj::Collection { \
    LIBJ_MUTABLE_DECLS(T, libj::Collection)

}  // namespace libj

#endif  // LIBJ_COLLECTION_H_