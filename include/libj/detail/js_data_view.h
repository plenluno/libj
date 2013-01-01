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
        , offset_(byteOffset)
        , length_(byteLength) {
        assert(buffer_);
        assert(offset_ <= buffer_->byteLength());
        assert(length_ <= buffer_->byteLength());
        assert(offset_ + length_ <= buffer_->byteLength());
    }

    virtual libj::JsArrayBuffer::Ptr buffer() const {
        return buffer_;
    }

    virtual Size byteOffset() const {
        return offset_;
    }

    virtual Size byteLength() const {
        return length_;
    }

    virtual Boolean getInt8(Size byteOffset, Byte* value) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getInt8(offset, value);
    }

    virtual Boolean getUint8(Size byteOffset, UByte* value) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getUint8(offset, value);
    }

    virtual Boolean getInt16(
        Size byteOffset, Short* value, Boolean littleEndian = false) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getInt16(offset, value, littleEndian);
    }

    virtual Boolean getUint16(
        Size byteOffset, UShort* value, Boolean littleEndian = false) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getUint16(offset, value, littleEndian);
    }

    virtual Boolean getInt32(
        Size byteOffset, Int* value, Boolean littleEndian = false) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getInt32(offset, value, littleEndian);
    }

    virtual Boolean getUint32(
        Size byteOffset, UInt* value, Boolean littleEndian = false) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getUint32(offset, value, littleEndian);
    }

    virtual Boolean getFloat32(
        Size byteOffset, Float* value, Boolean littleEndian = false) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getFloat32(offset, value, littleEndian);
    }

    virtual Boolean getFloat64(
        Size byteOffset, Double* value, Boolean littleEndian = false) const {
        Size offset = offset_ + byteOffset;
        return buffer_->getFloat64(offset, value, littleEndian);
    }

    virtual Boolean setInt8(Size byteOffset, Byte value) {
        Size offset = offset_ + byteOffset;
        return buffer_->setInt8(offset, value);
    }

    virtual Boolean setUint8(Size byteOffset, UByte value) {
        Size offset = offset_ + byteOffset;
        return buffer_->setUint8(offset, value);
    }

    virtual Boolean setInt16(
        Size byteOffset, Short value, Boolean littleEndian = false) {
        Size offset = offset_ + byteOffset;
        return buffer_->setInt16(offset, value, littleEndian);
    }

    virtual Boolean setUint16(
        Size byteOffset, UShort value, Boolean littleEndian = false) {
        Size offset = offset_ + byteOffset;
        return buffer_->setUint16(offset, value, littleEndian);
    }

    virtual Boolean setInt32(
        Size byteOffset, Int value, Boolean littleEndian = false) {
        Size offset = offset_ + byteOffset;
        return buffer_->setInt32(offset, value, littleEndian);
    }

    virtual Boolean setUint32(
        Size byteOffset, UInt value, Boolean littleEndian = false) {
        Size offset = offset_ + byteOffset;
        return buffer_->setUint32(offset, value, littleEndian);
    }

    virtual Boolean setFloat32(
        Size byteOffset, Float value, Boolean littleEndian = false) {
        Size offset = offset_ + byteOffset;
        return buffer_->setFloat32(offset, value, littleEndian);
    }

    virtual Boolean setFloat64(
        Size byteOffset, Double value, Boolean littleEndian = false) {
        Size offset = offset_ + byteOffset;
        return buffer_->setFloat64(offset, value, littleEndian);
    }

    virtual String::CPtr toString() const {
        return String::create(
            static_cast<const Byte*>(buffer_->data()) + offset_,
            String::UTF8,
            length_);
    }

 private:
    JsArrayBuffer::Ptr buffer_;
    Size offset_;
    Size length_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_DATA_VIEW_H_
