// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_TYPED_ARRAY_H_
#define LIBJ_JS_TYPED_ARRAY_H_

#include "libj/typed_array_list.h"

namespace libj {

typedef TypedArrayList<Byte>    JsInt8Array;
typedef TypedArrayList<Short>   JsInt16Array;
typedef TypedArrayList<Int>     JsInt32Array;
typedef TypedArrayList<UByte>   JsUInt8Array;
typedef TypedArrayList<UShort>  JsUInt16Array;
typedef TypedArrayList<UInt>    JsUInt32Array;
typedef TypedArrayList<Float>   JsFloat32Array;
typedef TypedArrayList<Double>  JsFloat64Array;

}  // namespace libj

#endif  // LIBJ_JS_TYPED_ARRAY_H_
