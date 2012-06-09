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

    virtual Byte getInt8(
        Size byteOffset) const = 0;
    virtual UByte getUInt8(
        Size byteOffset) const = 0;
    virtual Short getInt16(
        Size byteOffset, Boolean littleEndian = false) const = 0;
    virtual UShort getUInt16(
        Size byteOffset, Boolean littleEndian = false) const = 0;
    virtual Int getInt32(
        Size byteOffset, Boolean littleEndian = false) const = 0;
    virtual UInt getUInt32(
        Size byteOffset, Boolean littleEndian = false) const = 0;
    virtual Float getFloat32(
        Size byteOffset, Boolean littleEndian = false) const = 0;
    virtual Double getFloat64(
        Size byteOffset, Boolean littleEndian = false) const = 0;

    virtual void setInt8(
        Size byteOffset, Byte value) = 0;
    virtual void setUInt8(
        Size byteOffset, UByte value) = 0;
    virtual void setInt16(
        Size byteOffset, Short value, Boolean littleEndian = false) = 0;
    virtual void setUInt16(
        Size byteOffset, UShort value, Boolean littleEndian = false) = 0;
    virtual void setInt32(
        Size byteOffset, Int value, Boolean littleEndian = false) = 0;
    virtual void setUInt32(
        Size byteOffset, UInt value, Boolean littleEndian = false) = 0;
    virtual void setFloat32(
        Size byteOffset, Float value, Boolean littleEndian = false) = 0;
    virtual void setFloat64(
        Size byteOffset, Double value, Boolean littleEndian = false) = 0;
};

#define LIBJ_JS_ARRAY_BUFFER(T) public libj::JsArrayBuffer { \
    LIBJ_MUTABLE_DECLS(T, libj::JsArrayBuffer)

}  // namespace libj

#endif  // LIBJ_JS_ARRAY_BUFFER_H_
