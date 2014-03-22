// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_ITERATOR_H_
#define LIBJ_IMPL_ITERATOR_H_

#define LIBJ_ITERATOR_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Iterator>::id() || LIBJ_MUTABLE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_ITERATOR_H_
