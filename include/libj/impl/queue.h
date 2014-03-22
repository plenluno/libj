// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_QUEUE_H_
#define LIBJ_IMPL_QUEUE_H_

#define LIBJ_QUEUE_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Queue>::id() || LIBJ_COLLECTION_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_QUEUE_H_
