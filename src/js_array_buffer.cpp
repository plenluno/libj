// Copyright (c) 2012 Plenluno All rights reserved.

#include <algorithm>
#include "libj/js_array_buffer.h"
#include "libj/string.h"

namespace libj {

class JsArrayBufferImpl : public JsArrayBuffer {
 private:
    static const union endian_u {
        UShort one;
        UByte isLittle;
    } endian;

    template <typename T>
    T load(Size byteOffset, Boolean littleEndian) const {
        Boolean swap = endian.isLittle != littleEndian;
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
                if (endian.isLittle) {
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
        Boolean swap = endian.isLittle != littleEndian;
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

    Boolean isAscii() const {
        Size len64 = (length_ + 7) / 8;
        for (Size i = 0; i < len64; i++) {
            if (buf64_[i] & 0x8080808080808080) return false;
        }
        return true;
    }

 public:
    Size length() const {
        return length_;
    }

    JsArrayBuffer::Ptr slice(Size begin) const {
        return this->slice(begin, length_);
    }

    JsArrayBuffer::Ptr slice(Size begin, Size end) const {
        Size len = 0;
        if (begin < end && begin < length_) {
            if (end >= length_) end = length_;
            len = end - begin;
        }
        JsArrayBufferImpl* buf = new JsArrayBufferImpl(len);
        JsArrayBuffer::Ptr p(buf);
        if (len) {
            const Byte* src = reinterpret_cast<const Byte*>(buf64_);
            Byte *dst = reinterpret_cast<Byte*>(buf->buf64_);
            std::copy(src + begin, src + end, dst);
        }
        return p;
    }

    Boolean getInt8(Size byteOffset, Byte* value) const {
        UByte v;
        Boolean ret = getUInt8(byteOffset, &v);
        *value = v;
        return ret;
    }

    Boolean getUInt8(Size byteOffset, UByte* value) const {
        if (byteOffset >= length_) {
            return false;
        } else {
            const UByte* buf8 = reinterpret_cast<const UByte*>(buf64_);
            *value = buf8[byteOffset];
            return true;
        }
    }

    Boolean getInt16(
        Size byteOffset, Short* value, Boolean littleEndian = false) const {
        UShort v;
        Boolean ret = getUInt16(byteOffset, &v, littleEndian);
        *value = v;
        return ret;
    }

    Boolean getUInt16(
        Size byteOffset, UShort* value, Boolean littleEndian = false) const {
        if (byteOffset + 1 >= length_) {
            return false;
        } else {
            *value = load<UShort>(byteOffset, littleEndian);
            return true;
        }
    }

    Boolean getInt32(
        Size byteOffset, Int* value, Boolean littleEndian = false) const {
        UInt v;
        Boolean ret = getUInt32(byteOffset, &v, littleEndian);
        *value = v;
        return ret;
    }

    Boolean getUInt32(
        Size byteOffset, UInt* value, Boolean littleEndian = false) const {
        if (byteOffset + 3 >= length_) {
            return false;
         } else {
            *value = load<UInt>(byteOffset, littleEndian);
            return true;
        }
    }

    Boolean getFloat32(
        Size byteOffset, Float* value, Boolean littleEndian = false) const {
        union {
            Float f;
            UInt i;
        } v;
        Boolean ret =  getUInt32(byteOffset, &v.i, littleEndian);
        *value = v.f;
        return ret;
    }

    Boolean getFloat64(
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

    Boolean setInt8(Size byteOffset, Byte value) {
        return setUInt8(byteOffset, value);
    }

    Boolean setUInt8(Size byteOffset, UByte value) {
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
        return setUInt16(byteOffset, value, littleEndian);
    }

    Boolean setUInt16(
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
        return setUInt32(byteOffset, value, littleEndian);
    }

    Boolean setUInt32(
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
        union {
            Float f;
            UInt i;
        } v;
        v.f = value;
        return setUInt32(byteOffset, v.i, littleEndian);
    }

    Boolean setFloat64(
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

    String::CPtr toString() const {
        if (isAscii())
            return String::create(buf64_, String::ASCII, length_);
        else
            return String::create(buf64_, String::UTF8, length_);
    }

 private:
    Size length_;
    ULong* buf64_;

    JsArrayBufferImpl(Size length = 0)
        : length_(length)
        , buf64_(0) {
        Size len64 = (length + 7) / 8;
        if (len64) {
            buf64_ = new ULong[len64];
            buf64_[len64 - 1] = 0;
        }
    }

 public:
    ~JsArrayBufferImpl() {
        delete[] buf64_;
    }

    static JsArrayBuffer::Ptr create(Size length = 0) {
        JsArrayBuffer::Ptr p(new JsArrayBufferImpl(length));
        return p;
    }
};  // JsArrayBufferImpl
const union JsArrayBufferImpl::endian_u JsArrayBufferImpl::endian = {1};

JsArrayBuffer::Ptr JsArrayBuffer::create(Size length) {
    return JsArrayBufferImpl::create(length);
}

}   // namespace libj
