// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_COLLECTION_H_
#define LIBJ_IMPL_COLLECTION_H_

#define LIBJ_COLLECTION_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Collection>::id() || LIBJ_MUTABLE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_COLLECTION_H_
