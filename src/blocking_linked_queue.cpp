// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/blocking_linked_queue.h>
#include <libj/detail/blocking_linked_queue.h>

namespace libj {

BlockingLinkedQueue::Ptr BlockingLinkedQueue::create(Size capacity) {
    return Ptr(new detail::BlockingLinkedQueue<BlockingLinkedQueue>(capacity));
}

}  // namespace libj
