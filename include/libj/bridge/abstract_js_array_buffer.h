// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_JS_ARRAY_BUFFER_H_
#define LIBJ_BRIDGE_ABSTRACT_JS_ARRAY_BUFFER_H_

#include <libj/js_array_buffer.h>

namespace libj {
namespace bridge {

template<typename I>
class AbstractJsArrayBuffer : public I {
 public:
    AbstractJsArrayBuffer(
        JsArrayBuffer::Ptr buf = JsArrayBuffer::create())
        : buf_(buf) {}

    virtual Boolean isEmpty() const {
        return buf_->length() == 0;
    }

    virtual Size length() const {
        return buf_->length();
    }

    virtual const void* data() const {
        return buf_->data();
    }

    virtual Boolean shrink(Size length) {
        return buf_->shrink(length);
    }

    virtual Value slice(Size begin = 0, Size end = NO_POS) const {
        return buf_->slice(begin, end);
    }

    virtual Boolean getInt8(Size byteOffset, Byte* value) const {
        return buf_->getInt8(byteOffset, value);
    }

    virtual Boolean getUInt8(Size byteOffset, UByte* value) const {
        return buf_->getUInt8(byteOffset, value);
    }

    virtual Boolean getInt16(
        Size byteOffset, Short* value, Boolean littleEndian = false) const {
        return buf_->getInt16(byteOffset, value, littleEndian);
    }

    virtual Boolean getUInt16(
        Size byteOffset, UShort* value, Boolean littleEndian = false) const {
        return buf_->getUInt16(byteOffset, value, littleEndian);
    }

    virtual Boolean getInt32(
        Size byteOffset, Int* value, Boolean littleEndian = false) const {
        return buf_->getInt32(byteOffset, value, littleEndian);
    }

    virtual Boolean getUInt32(
        Size byteOffset, UInt* value, Boolean littleEndian = false) const {
        return buf_->getUInt32(byteOffset, value, littleEndian);
    }

    virtual Boolean getFloat32(
        Size byteOffset, Float* value, Boolean littleEndian = false) const {
        return buf_->getFloat32(byteOffset, value, littleEndian);
    }

    virtual Boolean getFloat64(
        Size byteOffset, Double* value, Boolean littleEndian = false) const {
        return buf_->getFloat64(byteOffset, value, littleEndian);
    }

    virtual Boolean setInt8(Size byteOffset, Byte value) {
        return buf_->setInt8(byteOffset, value);
    }

    virtual Boolean setUInt8(Size byteOffset, UByte value) {
        return buf_->setUInt8(byteOffset, value);
    }

    virtual Boolean setInt16(
        Size byteOffset, Short value, Boolean littleEndian = false) {
        return buf_->setInt16(byteOffset, value, littleEndian);
    }

    virtual Boolean setUInt16(
        Size byteOffset, UShort value, Boolean littleEndian = false) {
        return buf_->setUInt16(byteOffset, value, littleEndian);
    }

    virtual Boolean setInt32(
        Size byteOffset, Int value, Boolean littleEndian = false) {
        return buf_->setInt32(byteOffset, value, littleEndian);
    }

    virtual Boolean setUInt32(
        Size byteOffset, UInt value, Boolean littleEndian = false) {
        return buf_->setUInt32(byteOffset, value, littleEndian);
    }

    virtual Boolean setFloat32(
        Size byteOffset, Float value, Boolean littleEndian = false) {
        return buf_->setFloat32(byteOffset, value, littleEndian);
    }

    virtual Boolean setFloat64(
        Size byteOffset, Double value, Boolean littleEndian = false) {
        return buf_->setFloat64(byteOffset, value, littleEndian);
    }

    virtual String::CPtr toString() const {
        return buf_->toString();
    }

 private:
    JsArrayBuffer::Ptr buf_;
};

}  // namespace bridge
}  // namespace libj

#endif  // LIBJ_BRIDGE_ABSTRACT_JS_ARRAY_BUFFER_H_
