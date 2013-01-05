// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_CONCURRENT_LINKED_QUEUE_H_
#define LIBJ_CONCURRENT_LINKED_QUEUE_H_

#include <libj/queue.h>

namespace libj {

class ConcurrentLinkedQueue : LIBJ_QUEUE(ConcurrentLinkedQueue)
 public:
    static Ptr create();

    // Only suport the following methods:
    // virtual Boolean add(const Value& val) = 0;
    // virtual Boolean addAll(CPtr collection) = 0;
    // virtual void clear() = 0;
    // virtual Boolean isEmpty() const = 0;
    // virtual Boolean offer(const Value& val) = 0;
    // virtual Value poll() = 0;
    // virtual Value remove() = 0;
};

}  // namespace libj

#endif  // LIBJ_CONCURRENT_LINKED_QUEUE_H_
