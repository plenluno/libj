// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/concurrent_map.h>
#include <libj/detail/concurrent_map.h>

namespace libj {

ConcurrentMap::Ptr ConcurrentMap::create() {
    return Ptr(new detail::ConcurrentMap<ConcurrentMap>());
}

}  // namespace libj
