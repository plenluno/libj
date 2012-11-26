// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_JS_ARRAY_H_
#define LIBJ_TYPED_JS_ARRAY_H_

#include "libj/js_array.h"
#include "libj/typed_list.h"
#include "libj/detail/generic_js_array.h"

namespace libj {

template<typename T>
class TypedJsArray
    : public detail::GenericJsArray<T, TypedList<T, JsArray> > {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedJsArray, JsArray);

    static Ptr create();

    static Ptr create(Collection::CPtr c);

    virtual Value subList(Size from, Size to) const;
};

}  // namespace libj

#include "./detail/typed_js_array.h"

#endif  // LIBJ_TYPED_JS_ARRAY_H_
