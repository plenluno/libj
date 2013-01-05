// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_QUEUE_H_
#define LIBJ_QUEUE_H_

#include <libj/collection.h>

namespace libj {

class Queue : LIBJ_COLLECTION(Queue)
 public:
    virtual Value element() const = 0;

    virtual Boolean offer(const Value& val) = 0;

    virtual Value peek() const = 0;

    virtual Value poll() = 0;

    virtual Value remove() = 0;

    virtual Boolean remove(const Value& val) = 0;
};

}  // namespace libj

#define LIBJ_QUEUE(T) public libj::Queue { \
    LIBJ_MUTABLE_DEFS(T, libj::Queue)

#endif  // LIBJ_QUEUE_H_
