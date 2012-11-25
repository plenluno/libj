// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/set.h"
#include "libj/detail/set.h"

namespace libj {

Set::Ptr Set::create() {
    return Ptr(new detail::Set<Set>());
}

}  // namespace libj
