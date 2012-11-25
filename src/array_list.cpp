// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/array_list.h"
#include "libj/detail/array_list.h"

namespace libj {

ArrayList::Ptr ArrayList::create() {
    return Ptr(new detail::ArrayList<ArrayList>());
}

}  // namespace libj
