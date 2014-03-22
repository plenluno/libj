// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_LIST_H_
#define LIBJ_IMPL_LIST_H_

#define LIBJ_LIST_INSTANCEOF(ID) \
    (ID == libj::Type<libj::List>::id() || LIBJ_COLLECTION_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_LIST_H_
