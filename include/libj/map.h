// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_MAP_H_
#define LIBJ_MAP_H_

#include "libj/mutable.h"
#include "libj/set.h"

namespace libj {

class Map : LIBJ_MUTABLE(Map)
 public:
    virtual Size size() const = 0;
    virtual Value get(Value key) const;
    virtual Value put(Value key, Value val);
    virtual Value remove(Value key);
    virtual Type<Set>::Cptr keySet() const;
    virtual void clear() = 0;
    // and so on
};

}  // namespace libj

#endif  // LIBJ_MAP_H_