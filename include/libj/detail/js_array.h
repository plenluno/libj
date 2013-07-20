// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_ARRAY_H_
#define LIBJ_DETAIL_JS_ARRAY_H_

#include <libj/detail/generic_js_array.h>

namespace libj {
namespace detail {

template<typename I>
class JsArray : public GenericJsArray<I, Value> {
 public:
    virtual Boolean add(const Value& v) {
        return GenericJsArray<I, Value>::addTyped(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return GenericJsArray<I, Value>::addTyped(i, v);
    }

    virtual Boolean set(Size i, const Value& v) {
        return GenericJsArray<I, Value>::setTyped(i, v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_ARRAY_H_
