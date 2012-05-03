// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_FUNCTION_H_
#define LIBJ_FUNCTION_H_

#include "libj/mutable.h"
#include "libj/array_list.h"

namespace libj {

class Function : LIBJ_MUTABLE(Function)
 public:
    virtual Value operator()(Type<ArrayList>::Ptr args) = 0;
    
    virtual Type<String>::Cptr toString() const {
        // TODO: implement Function.toString
        return String::create();
    }
};

#define LIBJ_FUNCTION(T) public libj::Function { \
    LIBJ_MUTABLE_DECLS(T, libj::Function)

}  // namespace libj

#endif  // LIBJ_FUNCTION_H_
