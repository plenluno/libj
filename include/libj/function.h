// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_FUNCTION_H_
#define LIBJ_FUNCTION_H_

#include <libj/array_list.h>

namespace libj {

class Function : LIBJ_MUTABLE(Function)
 public:
    virtual Value operator()(ArrayList::Ptr args = ArrayList::null()) = 0;

    virtual Value call();

    virtual Value call(const Value& v1);

    virtual Value call(const Value& v1, const Value& v2);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6,
                       const Value& v7);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6,
                       const Value& v7, const Value& v8);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6,
                       const Value& v7, const Value& v8, const Value& v9);
};

}  // namespace libj

#include <libj/impl/function.h>

#define LIBJ_FUNCTION(T) public libj::Function { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_FUNCTION)

#define LIBJ_FUNCTION_TEMPLATE(T) public libj::Function { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_FUNCTION)

#endif  // LIBJ_FUNCTION_H_
