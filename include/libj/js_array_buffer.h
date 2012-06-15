// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_BUFFER_H_
#define LIBJ_JS_ARRAY_BUFFER_H_

#include "libj/mutable.h"

namespace libj {

class JsArrayBuffer : LIBJ_MUTABLE(JsArrayBuffer)
 public:
    static Ptr create(Size length = 0);

    virtual Size length() const = 0;

    virtual Ptr slice(Size begin) const = 0;
    virtual Ptr slice(Size begin, Size end) const = 0;

    virtual Boolean getInt8(
        Size byteOffset, Byte* value) const = 0;
    virtual Boolean getUInt8(
        Size byteOffset, UByte* value) const = 0;
    virtual Boolean getInt16(
        Size byteOffset, Short* value, Boolean littleEndian = false) const = 0;
    virtual Boolean getUInt16(
        Size byteOffset, UShort* value, Boolean littleEndian = false) const = 0;
    virtual Boolean getInt32(
        Size byteOffset, Int* value, Boolean littleEndian = false) const = 0;
    virtual Boolean getUInt32(
        Size byteOffset, UInt* value, Boolean littleEndian = false) const = 0;
    virtual Boolean getFloat32(
        Size byteOffset, Float* value, Boolean littleEndian = false) const = 0;
    virtual Boolean getFloat64(
        Size byteOffset, Double* value, Boolean littleEndian = false) const = 0;

    virtual Boolean setInt8(
        Size byteOffset, Byte value) = 0;
    virtual Boolean setUInt8(
        Size byteOffset, UByte value) = 0;
    virtual Boolean setInt16(
        Size byteOffset, Short value, Boolean littleEndian = false) = 0;
    virtual Boolean setUInt16(
        Size byteOffset, UShort value, Boolean littleEndian = false) = 0;
    virtual Boolean setInt32(
        Size byteOffset, Int value, Boolean littleEndian = false) = 0;
    virtual Boolean setUInt32(
        Size byteOffset, UInt value, Boolean littleEndian = false) = 0;
    virtual Boolean setFloat32(
        Size byteOffset, Float value, Boolean littleEndian = false) = 0;
    virtual Boolean setFloat64(
        Size byteOffset, Double value, Boolean littleEndian = false) = 0;
};

#define LIBJ_JS_ARRAY_BUFFER(T) public libj::JsArrayBuffer { \
    LIBJ_MUTABLE_DECLS(T, libj::JsArrayBuffer)

}  // namespace libj

#endif  // LIBJ_JS_ARRAY_BUFFER_H_
