// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_MAP_H_
#define LIBJ_MAP_H_

#include "libj/mutable.h"
#include "libj/set.h"

namespace libj {

class Map : LIBJ_MUTABLE(Map)
 public:
    virtual Size size() const = 0;
    virtual Value get(Type<Object>::Cptr obj) const;
    virtual Value put(Type<Object>::Cptr obj, Value val);
    virtual Value remove(Type<Object>::Cptr obj);
    virtual Type<Set>::Cptr keySet() const;
    virtual void clear() = 0;
    // and so on
};

}  // namespace libj

#endif  // LIBJ_MAP_H_