// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_BUFFER_H_
#define LIBJ_JS_ARRAY_BUFFER_H_

#include <libj/constant.h>
#include <libj/mutable.h>

namespace libj {

class JsArrayBuffer : LIBJ_MUTABLE(JsArrayBuffer)
 public:
    static Ptr create(Size length);

    virtual const void* data() const = 0;

    virtual Size byteLength() const = 0;

    virtual Ptr slice(Size begin = 0, Size end = NO_POS) const = 0;
};

}  // namespace libj

#define LIBJ_JS_ARRAY_BUFFER(T) public libj::JsArrayBuffer { \
    LIBJ_MUTABLE_DEFS(T, libj::JsArrayBuffer)

#endif  // LIBJ_JS_ARRAY_BUFFER_H_
