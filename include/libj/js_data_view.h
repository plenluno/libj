// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_JS_DATA_VIEW_H_
#define LIBJ_JS_DATA_VIEW_H_

#include <libj/js_array_buffer_view.h>

namespace libj {

class JsDataView : LIBJ_JS_ARRAY_BUFFER_VIEW(JsDataView)
 public:
    static Ptr create(Size length = 0);

    static Ptr create(
        JsArrayBuffer::Ptr buffer,
        Size byteOffset = NO_SIZE,
        Size byteLength = NO_SIZE);

    virtual Boolean getInt8(
        Size byteOffset,
        Byte* value) const = 0;

    virtual Boolean getUint8(
        Size byteOffset,
        UByte* value) const = 0;

    virtual Boolean getInt16(
        Size byteOffset,
        Short* value,
        Boolean littleEndian = false) const = 0;

    virtual Boolean getUint16(
        Size byteOffset,
        UShort* value,
        Boolean littleEndian = false) const = 0;

    virtual Boolean getInt32(
        Size byteOffset,
        Int* value,
        Boolean littleEndian = false) const = 0;

    virtual Boolean getUint32(
        Size byteOffset,
        UInt* value,
        Boolean littleEndian = false) const = 0;

    virtual Boolean getFloat32(
        Size byteOffset,
        Float* value,
        Boolean littleEndian = false) const = 0;

    virtual Boolean getFloat64(
        Size byteOffset,
        Double* value,
        Boolean littleEndian = false) const = 0;

    virtual Boolean setInt8(
        Size byteOffset,
        Byte value) = 0;

    virtual Boolean setUint8(
        Size byteOffset,
        UByte value) = 0;

    virtual Boolean setInt16(
        Size byteOffset,
        Short value,
        Boolean littleEndian = false) = 0;

    virtual Boolean setUint16(
        Size byteOffset,
        UShort value,
        Boolean littleEndian = false) = 0;

    virtual Boolean setInt32(
        Size byteOffset,
        Int value,
        Boolean littleEndian = false) = 0;

    virtual Boolean setUint32(
        Size byteOffset,
        UInt value,
        Boolean littleEndian = false) = 0;

    virtual Boolean setFloat32(
        Size byteOffset,
        Float value,
        Boolean littleEndian = false) = 0;

    virtual Boolean setFloat64(
        Size byteOffset,
        Double value,
        Boolean littleEndian = false) = 0;
};

}  // namespace libj

#endif  // LIBJ_JS_DATA_VIEW_H_
