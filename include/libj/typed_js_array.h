// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_JS_ARRAY_H_
#define LIBJ_TYPED_JS_ARRAY_H_

#include <libj/js_array.h>
#include <libj/typed_list.h>
#include <libj/detail/generic_js_array.h>

namespace libj {

template<typename T>
class TypedJsArray : LIBJ_TYPED_LIST(JsArray, T)
 public:
    static Ptr create();

    static Ptr create(Collection::CPtr c);

    virtual Value subList(Size from, Size to) const;
};

}  // namespace libj

#include <libj/impl/typed_js_array.h>

#endif  // LIBJ_TYPED_JS_ARRAY_H_
