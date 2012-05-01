// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_SHARED_PTR_H_
#define LIBJ_SHARED_PTR_H_

#define LIBJ_DISABLE_BOOST_SP_GET_DELETER
#include "boost/shared_ptr.hpp"

namespace libj {

template<typename T>
struct SharedPtr {
    typedef boost::shared_ptr<T> Type;
};

}  // namespace libj

#endif  // LIBJ_SHARED_PTR_H_
