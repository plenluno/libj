// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_ARRAY_BUFFER_H_
#define LIBJ_DETAIL_JS_ARRAY_BUFFER_H_

#include <libj/endian.h>
#include <libj/string.h>
#include <libj/js_array_buffer.h>

namespace libj {
namespace detail {

class JsArrayBuffer : LIBJ_JS_ARRAY_BUFFER(JsArrayBuffer)
 public:
    JsArrayBuffer(Size length)
        : length_(length)
        , buf64_(0) {
        if (length) {
            Size len64 = (length + 7) >> 3;
            buf64_ = new ULong[len64 + 1];
            for (Size i = 0; i <= len64; i++) {
                buf64_[i] = 0;
            }
        }
    }

    virtual ~JsArrayBuffer() {
        delete[] buf64_;
    }

    virtual const void* data() const {
        return buf64_;
    }

    virtual Size byteLength() const {
        return length_;
    }

    virtual libj::JsArrayBuffer::Ptr slice(Size begin, Size end) const {
        Size len = 0;
        if (begin < end && begin < length_) {
            if (end >= length_) end = length_;
            len = end - begin;
        }
        JsArrayBuffer* buf = new JsArrayBuffer(len);
        if (len) {
            const Byte* src = reinterpret_cast<const Byte*>(buf64_);
            Byte *dst = reinterpret_cast<Byte*>(buf->buf64_);
            std::copy(src + begin, src + end, dst);
        }
        return Ptr(buf);
    }

    virtual String::CPtr toString() const {
        return String::create(buf64_, String::UTF8);
    }

 public:
    Boolean getInt8(Size byteOffset, Byte* value) const {
        return getUint8(byteOffset, reinterpret_cast<UByte*>(value));
    }

    Boolean getUint8(Size byteOffset, UByte* value) const {
        if (!value || byteOffset >= length_) {
            return false;
        } else {
            const UByte* buf8 = reinterpret_cast<const UByte*>(buf64_);
            *value = buf8[byteOffset];
            return true;
        }
    }

    Boolean getInt16(
        Size byteOffset, Short* value, Boolean littleEndian = false) const {
        return getUint16(
            byteOffset, reinterpret_cast<UShort*>(value), littleEndian);
    }

    Boolean getUint16(
        Size byteOffset, UShort* value, Boolean littleEndian = false) const {
        if (!value || byteOffset + 1 >= length_) {
            return false;
        } else {
            *value = load<UShort>(byteOffset, littleEndian);
            return true;
        }
    }

    Boolean getInt32(
        Size byteOffset, Int* value, Boolean littleEndian = false) const {
        return getUint32(
            byteOffset, reinterpret_cast<UInt*>(value), littleEndian);
    }

    Boolean getUint32(
        Size byteOffset, UInt* value, Boolean littleEndian = false) const {
        if (!value || byteOffset + 3 >= length_) {
            return false;
         } else {
            *value = load<UInt>(byteOffset, littleEndian);
            return true;
        }
    }

    Boolean getFloat32(
        Size byteOffset, Float* value, Boolean littleEndian = false) const {
        if (!value || byteOffset + 3 >= length_) {
            return false;
        } else {
            union {
                UInt ui;
                Float f;
            } v;
            v.ui = load<UInt>(byteOffset, littleEndian);
            *value = v.f;
            return true;
        }
    }

    Boolean getFloat64(
        Size byteOffset, Double* value, Boolean littleEndian = false) const {
        if (!value || byteOffset + 7 >= length_) {
            return false;
        } else {
            union {
                ULong ul;
                Double d;
            } v;
            v.ul = load<ULong>(byteOffset, littleEndian);
            *value = v.d;
            return true;
        }
    }

    Boolean setInt8(Size byteOffset, Byte value) {
        return setUint8(byteOffset, value);
    }

    Boolean setUint8(Size byteOffset, UByte value) {
        if (byteOffset >= length_) {
            return false;
        } else {
            UByte* buf8 = reinterpret_cast<UByte*>(buf64_);
            buf8[byteOffset] = value;
            return true;
        }
    }

    Boolean setInt16(
        Size byteOffset, Short value, Boolean littleEndian = false) {
        return setUint16(byteOffset, value, littleEndian);
    }

    Boolean setUint16(
        Size byteOffset, UShort value, Boolean littleEndian = false) {
        if (byteOffset + 1 >= length_) {
            return false;
        } else {
            store<UShort>(byteOffset, value, littleEndian);
            return true;
        }
    }

    Boolean setInt32(
        Size byteOffset, Int value, Boolean littleEndian = false) {
        return setUint32(byteOffset, value, littleEndian);
    }

    Boolean setUint32(
        Size byteOffset, UInt value, Boolean littleEndian = false) {
        if (byteOffset + 3 >= length_) {
            return false;
        } else {
            store<UInt>(byteOffset, value, littleEndian);
            return true;
        }
    }

    Boolean setFloat32(
        Size byteOffset, Float value, Boolean littleEndian = false) {
        if (byteOffset + 3 >= length_) {
            return false;
        } else {
            union {
                UInt ui;
                Float f;
            } v;
            v.f = value;
            store<UInt>(byteOffset, v.ui, littleEndian);
            return true;
        }
    }

    Boolean setFloat64(
        Size byteOffset, Double value, Boolean littleEndian = false) {
        if (byteOffset + 7 >= length_) {
            return false;
        } else {
            union {
                ULong ul;
                Double d;
            } v;
            v.d = value;
            store<ULong>(byteOffset, v.ul, littleEndian);
            return true;
        }
    }

 private:
    static Boolean isLittleEndian() {
        static Boolean little = endian() == LITTLE;
        return little;
    }

    template <typename T>
    T load(Size byteOffset, Boolean littleEndian) const {
        Boolean swap = isLittleEndian() != littleEndian;
        if (swap) {
            union {
                T w;
                UByte b[sizeof(T)];
            } d;
            const UByte* src = reinterpret_cast<const UByte*>(buf64_);
            src += byteOffset;
            UByte* dst = d.b + sizeof(T) - 1;
            for (Size i = 0; i < sizeof(T); i++)
                *dst-- = *src++;
            return d.w;
        } else {
            const T* buf = reinterpret_cast<const T*>(buf64_);
            Size idx = byteOffset / sizeof(T);
            Size mod = byteOffset % sizeof(T);
            T d0 = buf[idx];
            if (mod) {
                T d1 = buf[idx + 1];
                Size sh = mod * 8;
                if (isLittleEndian()) {
                    d0 = d0 >> sh;
                    d1 = d1 << (8 * sizeof(T) - sh);
                } else {
                    d0 = d0 << sh;
                    d1 = d1 >> (8 * sizeof(T) - sh);
                }
                d0 = d0 | d1;
            }
            return d0;
        }
    }

    template <typename T>
    void store(Size byteOffset, T value, Boolean littleEndian) {
        Boolean swap = isLittleEndian() != littleEndian;
        if (swap || byteOffset % sizeof(T)) {
            union {
                T w;
                UByte b[sizeof(T)];
            } d;
            d.w = value;
            UByte* dst = reinterpret_cast<UByte*>(buf64_);
            dst += byteOffset;
            if (swap) {
                const UByte* src = d.b + sizeof(T) - 1;
                for (Size i = 0; i < sizeof(T); i++)
                    *dst++ = *src--;
            } else {
                const UByte* src = d.b;
                for (Size i = 0; i < sizeof(T); i++)
                    *dst++ = *src++;
            }
        } else {
            T* buf = reinterpret_cast<T*>(buf64_);
            Size idx = byteOffset / sizeof(T);
            buf[idx] = value;
        }
    }

 private:
    Size length_;
    ULong* buf64_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_ARRAY_BUFFER_H_
