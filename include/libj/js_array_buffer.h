// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_BUFFER_H_
#define LIBJ_JS_ARRAY_BUFFER_H_

#include "libj/constant.h"
#include "libj/mutable.h"
#include "libj/value.h"

namespace libj {

class JsArrayBuffer : LIBJ_MUTABLE(JsArrayBuffer)
 public:
    static Ptr create(Size length = 0);

    virtual Size length() const = 0;
    virtual const void* data() const = 0;
    virtual Boolean shrink(Size length) = 0;
    virtual Value slice(Size begin = 0, Size end = NO_POS) const = 0;

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

 public:
    Boolean isEmpty() const {
        return length() == 0;
    }
};

#define LIBJ_JS_ARRAY_BUFFER(T) public libj::JsArrayBuffer { \
    LIBJ_MUTABLE_DEFS(T, libj::JsArrayBuffer)

#define LIBJ_JS_ARRAY_BUFFER_IMPL(B) \
public: \
    Size length() const { \
        return B->length(); \
    } \
    const void* data() const { \
        return B->data(); \
    } \
    Boolean getInt8( \
        Size byteOffset, Byte* value) const { \
        return B->getInt8(byteOffset, value); \
    } \
    Boolean getUInt8( \
        Size byteOffset, UByte* value) const { \
        return B->getUInt8(byteOffset, value); \
    } \
    Boolean getInt16( \
        Size byteOffset, Short* value, Boolean littleEndian = false) const { \
        return B->getInt16(byteOffset, value, littleEndian); \
    } \
    Boolean getUInt16( \
        Size byteOffset, UShort* value, Boolean littleEndian = false) const { \
        return B->getUInt16(byteOffset, value, littleEndian); \
    } \
    Boolean getInt32( \
        Size byteOffset, Int* value, Boolean littleEndian = false) const { \
        return B->getInt32(byteOffset, value, littleEndian); \
    } \
    Boolean getUInt32( \
        Size byteOffset, UInt* value, Boolean littleEndian = false) const { \
        return B->getUInt32(byteOffset, value, littleEndian); \
    } \
    Boolean getFloat32( \
        Size byteOffset, Float* value, Boolean littleEndian = false) const { \
        return B->getFloat32(byteOffset, value, littleEndian); \
    } \
    Boolean getFloat64( \
        Size byteOffset, Double* value, Boolean littleEndian = false) const { \
        return B->getFloat64(byteOffset, value, littleEndian); \
    } \
    Boolean setInt8( \
        Size byteOffset, Byte value) { \
        return B->setInt8(byteOffset, value); \
    } \
    Boolean setUInt8( \
        Size byteOffset, UByte value) { \
        return B->setUInt8(byteOffset, value); \
    } \
    Boolean setInt16( \
        Size byteOffset, Short value, Boolean littleEndian = false) { \
        return B->setInt16(byteOffset, value, littleEndian); \
    } \
    Boolean setUInt16( \
        Size byteOffset, UShort value, Boolean littleEndian = false) { \
        return B->setUInt16(byteOffset, value, littleEndian); \
    } \
    Boolean setInt32( \
        Size byteOffset, Int value, Boolean littleEndian = false) { \
        return B->setInt32(byteOffset, value, littleEndian); \
    } \
    Boolean setUInt32( \
        Size byteOffset, UInt value, Boolean littleEndian = false) { \
        return B->setUInt32(byteOffset, value, littleEndian); \
    } \
    Boolean setFloat32( \
        Size byteOffset, Float value, Boolean littleEndian = false) { \
        return B->setFloat32(byteOffset, value, littleEndian); \
    } \
    Boolean setFloat64( \
        Size byteOffset, Double value, Boolean littleEndian = false) { \
        return B->setFloat64(byteOffset, value, littleEndian); \
    } \
    String::CPtr toString() const { \
        return B->toString(); \
    }

}  // namespace libj

#endif  // LIBJ_JS_ARRAY_BUFFER_H_
