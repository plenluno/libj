// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_ARRAY_LIST_H_
#define LIBJ_IMPL_ARRAY_LIST_H_

#define LIBJ_ARRAY_LIST_INSTANCEOF(ID) \
    (ID == libj::Type<libj::ArrayList>::id() || LIBJ_LIST_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_ARRAY_LIST_H_
