// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_MAP_H_
#define LIBJ_IMPL_MAP_H_

#define LIBJ_MAP_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Map>::id() || LIBJ_MUTABLE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_MAP_H_
