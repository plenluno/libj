// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_CLOSURE_H_
#define LIBJ_DETAIL_JS_CLOSURE_H_

#include <libj/js_array.h>

namespace libj {
namespace detail {

typedef std::function<Value(JsArray::Ptr)> JsLambda;

template<typename I>
class JsClosure : public I {
 public:
    JsClosure(JsLambda lambda) : lambda_(lambda) {}

    virtual Value operator()(JsArray::Ptr args) {
        return lambda_(args);
    }

 private:
    JsLambda lambda_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_CLOSURE_H_
