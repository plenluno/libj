// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ARRAY_H_
#define LIBJ_TYPED_ARRAY_H_

#include "libj/typed_array_list.h"

namespace libj {

typedef TypedArrayList<Byte>    Int8Array;
typedef TypedArrayList<Short>   Int16Array;
typedef TypedArrayList<Int>     Int32Array;
typedef TypedArrayList<UByte>   UInt8Array;
typedef TypedArrayList<UShort>  UInt16Array;
typedef TypedArrayList<UInt>    UInt32Array;
typedef TypedArrayList<Float>   Float32Array;
typedef TypedArrayList<Double>  Float64Array;

}  // namespace libj

#endif  // LIBJ_TYPED_ARRAY_H_
