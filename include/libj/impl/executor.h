// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_EXECUTOR_H_
#define LIBJ_IMPL_EXECUTOR_H_

#define LIBJ_EXECUTOR_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Executor>::id() || LIBJ_MUTABLE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_EXECUTOR_H_
