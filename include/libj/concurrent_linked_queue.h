// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_CONCURRENT_LINKED_QUEUE_H_
#define LIBJ_CONCURRENT_LINKED_QUEUE_H_

#include <libj/queue.h>

namespace libj {

class ConcurrentLinkedQueue : LIBJ_QUEUE(ConcurrentLinkedQueue)
 public:
    static Ptr create();
};

}  // namespace libj

#endif  // LIBJ_CONCURRENT_LINKED_QUEUE_H_
