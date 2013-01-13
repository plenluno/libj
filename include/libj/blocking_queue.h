// Copyright (c) 2013 Plenluno All rights reserved.

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

#define LIBJ_BLOCKING_QUEUE(T) public libj::BlockingQueue { \
    LIBJ_MUTABLE_DEFS(T, libj::BlockingQueue)

#endif  // LIBJ_BLOCKING_QUEUE_H_
