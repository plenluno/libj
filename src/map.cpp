// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/map.h>
#include <libj/detail/map.h>

namespace libj {

Map::Ptr Map::create() {
    return Ptr(new detail::Map<Map>());
}

}  // namespace libj
