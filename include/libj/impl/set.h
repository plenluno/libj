// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_SET_H_
#define LIBJ_IMPL_SET_H_

#define LIBJ_SET_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Set>::id() || LIBJ_COLLECTION_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_SET_H_
