// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_BLOCKING_QUEUE_H_
#define LIBJ_IMPL_BLOCKING_QUEUE_H_

#define LIBJ_BLOCKING_QUEUE_INSTANCEOF(ID) \
    (ID == libj::Type<libj::BlockingQueue>::id() || LIBJ_QUEUE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_BLOCKING_QUEUE_H_
