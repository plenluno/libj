// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_BLOCKING_LINKED_QUEUE_H_
#define LIBJ_DETAIL_BLOCKING_LINKED_QUEUE_H_

#include <libj/detail/blocking_queue.h>
#include <libj/detail/linked_list.h>

namespace libj {
namespace detail {

template<typename I>
class BlockingLinkedQueue : public BlockingQueue<LinkedList<I> > {
 public:
    BlockingLinkedQueue(Size capacity = 0)  // '0' means unlimited
        : BlockingQueue<LinkedList<I> >(capacity) {}
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_BLOCKING_LINKED_QUEUE_H_
