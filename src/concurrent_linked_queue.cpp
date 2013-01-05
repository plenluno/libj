// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/concurrent_linked_queue.h>
#include <libj/detail/concurrent_linked_queue.h>

namespace libj {

ConcurrentLinkedQueue::Ptr ConcurrentLinkedQueue::create() {
    return Ptr(new detail::ConcurrentLinkedQueue<ConcurrentLinkedQueue>());
}

}  // namespace libj
