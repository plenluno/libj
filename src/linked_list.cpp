// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/linked_list.h"
#include "libj/detail/linked_list.h"

namespace libj {

LinkedList::Ptr LinkedList::create() {
    return Ptr(new detail::LinkedList<LinkedList>());
}

}  // namespace libj
