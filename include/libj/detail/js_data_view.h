// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_DATA_VIEW_H_
#define LIBJ_DETAIL_JS_DATA_VIEW_H_

#include <libj/cast.h>
#include <libj/string.h>
#include <libj/detail/js_array_buffer.h>

#include <assert.h>

namespace libj {
namespace detail {

template<typename I>
class JsDataView : public I {
 public:
    typedef typename I::Ptr Ptr;
    typedef typename I::CPtr CPtr;

    JsDataView(
        libj::JsArrayBuffer::Ptr buffer,
        Size byteOffset,
        Size byteLength)
        : buffer_(LIBJ_STATIC_PTR_CAST(JsArrayBuffer)(buffer))
        , byteOffset_(byteOffset)
        , byteLength_(byteLength) {
        assert(buffer_);
        assert(byteOffset_ <= buffer_->byteLength());
        assert(byteLength_ <= buffer_->byteLength());
        assert(byteOffset_ + byteLength_ <= buffer_->byteLength());
    }

    virtual libj::JsArrayBuffer::Ptr buffer() const {
        return buffer_;
    }

    virtual Size byteOffset() const {
        return byteOffset_;
    }

    virtual Size byteLength() const {
        return byteLength_;
    }

    virtual Boolean getInt8(Size byteOffset, Byte* value) const {
        return buffer_->getInt8(byteOffset, value);
    }

    virtual Boolean getUint8(Size byteOffset, UByte* value) const {
        return buffer_->getUint8(byteOffset, value);
    }

    virtual Boolean getInt16(
        Size byteOffset, Short* value, Boolean littleEndian = false) const {
        return buffer_->getInt16(byteOffset, value, littleEndian);
    }

    virtual Boolean getUint16(
        Size byteOffset, UShort* value, Boolean littleEndian = false) const {
        return buffer_->getUint16(byteOffset, value, littleEndian);
    }

    virtual Boolean getInt32(
        Size byteOffset, Int* value, Boolean littleEndian = false) const {
        return buffer_->getInt32(byteOffset, value, littleEndian);
    }

    virtual Boolean getUint32(
        Size byteOffset, UInt* value, Boolean littleEndian = false) const {
        return buffer_->getUint32(byteOffset, value, littleEndian);
    }

    virtual Boolean getFloat32(
        Size byteOffset, Float* value, Boolean littleEndian = false) const {
        return buffer_->getFloat32(byteOffset, value, littleEndian);
    }

    virtual Boolean getFloat64(
        Size byteOffset, Double* value, Boolean littleEndian = false) const {
        return buffer_->getFloat64(byteOffset, value, littleEndian);
    }

    virtual Boolean setInt8(Size byteOffset, Byte value) {
        return buffer_->setInt8(byteOffset, value);
    }

    virtual Boolean setUint8(Size byteOffset, UByte value) {
        return buffer_->setUint8(byteOffset, value);
    }

    virtual Boolean setInt16(
        Size byteOffset, Short value, Boolean littleEndian = false) {
        return buffer_->setInt16(byteOffset, value, littleEndian);
    }

    virtual Boolean setUint16(
        Size byteOffset, UShort value, Boolean littleEndian = false) {
        return buffer_->setUint16(byteOffset, value, littleEndian);
    }

    virtual Boolean setInt32(
        Size byteOffset, Int value, Boolean littleEndian = false) {
        return buffer_->setInt32(byteOffset, value, littleEndian);
    }

    virtual Boolean setUint32(
        Size byteOffset, UInt value, Boolean littleEndian = false) {
        return buffer_->setUint32(byteOffset, value, littleEndian);
    }

    virtual Boolean setFloat32(
        Size byteOffset, Float value, Boolean littleEndian = false) {
        return buffer_->setFloat32(byteOffset, value, littleEndian);
    }

    virtual Boolean setFloat64(
        Size byteOffset, Double value, Boolean littleEndian = false) {
        return buffer_->setFloat64(byteOffset, value, littleEndian);
    }

    virtual String::CPtr toString() const {
        return String::create(
            static_cast<const Byte*>(buffer_->data()) + byteOffset_,
            String::UTF8,
            byteLength_);
    }

 private:
    JsArrayBuffer::Ptr buffer_;
    Size byteOffset_;
    Size byteLength_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_DATA_VIEW_H_
