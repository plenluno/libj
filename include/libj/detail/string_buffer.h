// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STRING_BUFFER_H_
#define LIBJ_DETAIL_STRING_BUFFER_H_

#include <libj/string_buffer.h>
#include <libj/detail/scoped_lock.h>
#include <libj/detail/string_builder.h>

namespace libj {
namespace detail {

class StringBuffer : public StringBuilder<libj::StringBuffer> {
 public:
    virtual Size length() const {
        ScopedLock lock(mutex_);
        return StringBuilder::length();
    }

    virtual Char charAt(Size index) const {
        ScopedLock lock(mutex_);
        return StringBuilder::charAt(index);
    }

    virtual Ptr append(const Value& val) {
        ScopedLock lock(mutex_);
        return StringBuilder::append(val);
    }

    virtual Ptr appendChar(Char c) {
        ScopedLock lock(mutex_);
        return StringBuilder::appendChar(c);
    }

    virtual Ptr appendStr(const char* str) {
        ScopedLock lock(mutex_);
        return StringBuilder::appendStr(str);
    }

    virtual Ptr appendStr(const Char* str) {
        ScopedLock lock(mutex_);
        return StringBuilder::appendStr(str);
    }

    virtual Boolean setCharAt(Size index, Char c) {
        ScopedLock lock(mutex_);
        return StringBuilder::setCharAt(index, c);
    }

    virtual String::CPtr toString() const {
        ScopedLock lock(mutex_);
        return StringBuilder::toString();
    }

    virtual const Char* data() const {
        ScopedLock lock(mutex_);
        return StringBuilder::data();
    }

 private:
    mutable Mutex mutex_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_STRING_BUFFER_H_
