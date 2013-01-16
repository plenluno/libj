// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_BLOCKING_LINKED_QUEUE_H_
#define LIBJ_BLOCKING_LINKED_QUEUE_H_

#include <libj/constant.h>
#include <libj/blocking_queue.h>

namespace libj {

class BlockingLinkedQueue : LIBJ_BLOCKING_QUEUE(BlockingLinkedQueue)
 public:
    static Ptr create(Size capacity = NO_SIZE);
};

}  // namespace libj

#endif  // LIBJ_BLOCKING_LINKED_QUEUE_H_
