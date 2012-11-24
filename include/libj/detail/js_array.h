// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_ARRAY_H_
#define LIBJ_DETAIL_JS_ARRAY_H_

#include "libj/js_array.h"

#include "./generic_js_array.h"

namespace libj {
namespace detail {

template<typename I>
class JsArray : public GenericJsArray<Value, I> {
 public:
    virtual Boolean add(const Value& v) {
        return this->addTyped(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return this->addTyped(i, v);
    }

    virtual Boolean set(Size i, const Value& v) {
        return this->setTyped(i, v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_ARRAY_H_
