// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_ARRAY_BUFFER_H_
#define LIBJ_DETAIL_JS_ARRAY_BUFFER_H_

#include <algorithm>

#include "libj/endian.h"
#include "libj/string.h"

namespace libj {
namespace detail {

template<typename I>
class JsArrayBuffer : public I {
 public:
    typedef typename I::Ptr Ptr;
    typedef typename I::CPtr CPtr;

    JsArrayBuffer(Size length = 0)
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

    virtual Boolean isEmpty() const {
        return length() == 0;
    }

    virtual Size length() const {
        return length_;
    }

    virtual const void* data() const {
        return buf64_;
    }

    virtual Boolean shrink(Size length) {
        if (length > length_) {
            return false;
        } else {
            length_ = length;
            if (!length) {
                delete[] buf64_;
                buf64_ = NULL;
            }
            return true;
        }
    }

    virtual Value slice(Size begin, Size end) const {
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

    virtual Boolean getInt8(Size byteOffset, Byte* value) const {
        UByte v;
        Boolean ret = getUInt8(byteOffset, &v);
        *value = v;
        return ret;
    }

    virtual Boolean getUInt8(Size byteOffset, UByte* value) const {
        if (byteOffset >= length_) {
            return false;
        } else {
            const UByte* buf8 = reinterpret_cast<const UByte*>(buf64_);
            *value = buf8[byteOffset];
            return true;
        }
    }

    virtual Boolean getInt16(
        Size byteOffset, Short* value, Boolean littleEndian = false) const {
        UShort v;
        Boolean ret = getUInt16(byteOffset, &v, littleEndian);
        *value = v;
        return ret;
    }

    virtual Boolean getUInt16(
        Size byteOffset, UShort* value, Boolean littleEndian = false) const {
        if (byteOffset + 1 >= length_) {
            return false;
        } else {
            *value = load<UShort>(byteOffset, littleEndian);
            return true;
        }
    }

    virtual Boolean getInt32(
        Size byteOffset, Int* value, Boolean littleEndian = false) const {
        UInt v;
        Boolean ret = getUInt32(byteOffset, &v, littleEndian);
        *value = v;
        return ret;
    }

    virtual Boolean getUInt32(
        Size byteOffset, UInt* value, Boolean littleEndian = false) const {
        if (byteOffset + 3 >= length_) {
            return false;
         } else {
            *value = load<UInt>(byteOffset, littleEndian);
            return true;
        }
    }

    virtual Boolean getFloat32(
        Size byteOffset, Float* value, Boolean littleEndian = false) const {
        union {
            Float f;
            UInt i;
        } v;
        Boolean ret =  getUInt32(byteOffset, &v.i, littleEndian);
        *value = v.f;
        return ret;
    }

    virtual Boolean getFloat64(
        Size byteOffset, Double* value, Boolean littleEndian = false) const {
        if (byteOffset + 7 >= length_) {
            return false;
        } else {
            union {
                ULong i;
                Double f;
            } v;
            v.i = load<ULong>(byteOffset, littleEndian);
            *value = v.f;
            return true;
        }
    }

    virtual Boolean setInt8(Size byteOffset, Byte value) {
        return setUInt8(byteOffset, value);
    }

    virtual Boolean setUInt8(Size byteOffset, UByte value) {
        if (byteOffset >= length_) {
            return false;
        } else {
            UByte* buf8 = reinterpret_cast<UByte*>(buf64_);
            buf8[byteOffset] = value;
            return true;
        }
    }

    virtual Boolean setInt16(
        Size byteOffset, Short value, Boolean littleEndian = false) {
        return setUInt16(byteOffset, value, littleEndian);
    }

    virtual Boolean setUInt16(
        Size byteOffset, UShort value, Boolean littleEndian = false) {
        if (byteOffset + 1 >= length_) {
            return false;
        } else {
            store<UShort>(byteOffset, value, littleEndian);
            return true;
        }
    }

    virtual Boolean setInt32(
        Size byteOffset, Int value, Boolean littleEndian = false) {
        return setUInt32(byteOffset, value, littleEndian);
    }

    virtual Boolean setUInt32(
        Size byteOffset, UInt value, Boolean littleEndian = false) {
        if (byteOffset + 3 >= length_) {
            return false;
        } else {
            store<UInt>(byteOffset, value, littleEndian);
            return true;
        }
    }

    virtual Boolean setFloat32(
        Size byteOffset, Float value, Boolean littleEndian = false) {
        union {
            Float f;
            UInt i;
        } v;
        v.f = value;
        return setUInt32(byteOffset, v.i, littleEndian);
    }

    virtual Boolean setFloat64(
        Size byteOffset, Double value, Boolean littleEndian = false) {
        if (byteOffset + 7 >= length_) {
            return false;
        } else {
            union {
                Double f;
                ULong i;
            } v;
            v.f = value;
            store<ULong>(byteOffset, v.i, littleEndian);
            return true;
        }
    }

    virtual String::CPtr toString() const {
        return String::create(buf64_, String::UTF8);
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
