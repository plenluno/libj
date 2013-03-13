// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_CONCURRENT_MAP_H_
#define LIBJ_CONCURRENT_MAP_H_

#include <libj/map.h>

namespace libj {

class ConcurrentMap : LIBJ_MAP(ConcurrentMap)
 public:
    static Ptr create();
};

}  // namespace libj

#endif  // LIBJ_CONCURRENT_MAP_H_
