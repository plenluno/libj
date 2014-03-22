// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_BLOCKING_QUEUE_H_
#define LIBJ_BLOCKING_QUEUE_H_

#include <libj/queue.h>

namespace libj {

class BlockingQueue : LIBJ_QUEUE(BlockingQueue)
 public:
    virtual void put(const Value& val) = 0;

    virtual Value take() = 0;
};

}  // namespace libj

#include <libj/impl/blocking_queue.h>

#define LIBJ_BLOCKING_QUEUE(T) public libj::BlockingQueue { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_BLOCKING_QUEUE)

#endif  // LIBJ_BLOCKING_QUEUE_H_
