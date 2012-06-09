// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_TYPED_ARRAY_H_
#define LIBJ_JS_TYPED_ARRAY_H_

#include "libj/typed_array_list.h"

namespace libj {

template<typename T>
class JsTypedArray : LIBJ_TYPED_ARRAY_LIST_TEMPLATE(JsTypedArray, T)
 public:
    static Ptr create() {
        Ptr p(new JsTypedArray());
        return p;
    }

     // TODO(plenluno): implement
     // static Ptr create(JsArrayBuffer::Ptr buf);
     // Ptr subArray(Size from);
     // Ptr subArray(Size from, Size to);
};

}  // namespace libj

#endif  // LIBJ_JS_TYPED_ARRAY_H_
