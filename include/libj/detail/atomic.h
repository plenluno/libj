// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_ATOMIC_H_
#define LIBJ_DETAIL_ATOMIC_H_

#include <libj/config.h>

#ifdef LIBJ_USE_CXX11
# include <atomic>
# define LIBJ_DETAIL_ATOMIC(T) std::atomic<T>
#else
# include <boost/atomic.hpp>
# define LIBJ_DETAIL_ATOMIC(T) boost::atomic<T>
#endif

#endif  // LIBJ_DETAIL_ATOMIC_H_
