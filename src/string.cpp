// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/symbol.h>
#include <libj/detail/string.h>
#include <libj/detail/to_string.h>

namespace libj {

String::CPtr String::create() {
    static const CPtr empty(intern(CPtr(new detail::String())));
    return empty;
}

String::CPtr String::create(Char c, Size n) {
    return CPtr(new detail::String(c, n));
}

String::CPtr String::create(const std::u16string& s16) {
    return CPtr(new detail::String(s16));
}

String::CPtr String::create(const std::u32string& s32) {
    return CPtr(new detail::String(s32));
}

String::CPtr String::create(
    const void* data, Encoding enc, Size len, Size max) {
    if (data) {
        return CPtr(new detail::String(data, enc, len, max));
    } else {
        return null();
    }
}

String::CPtr String::intern(String::CPtr str) {
    return detail::String::intern(str);
}

String::CPtr String::intern(
    const void* data, Encoding enc, Size len, Size max) {
    return intern(String::create(data, enc, len, max));
}

static inline String::CPtr objectToString(const Value& val) {
    LIBJ_STATIC_SYMBOL_DEF(symNull, "null");

    String::CPtr s = toCPtr<String>(val);
    if (s) return s;

    Object::CPtr o = toCPtr<Object>(val);
    if (o) {
        return o->toString();
    } else {
        return symNull;
    }
}

String::CPtr String::valueOf(const Value& val) {
    LIBJ_STATIC_SYMBOL_DEF(symUndefined, "undefined");

    const Size kLen = 64;
    char buf[kLen];
    if (val.isUndefined()) {
        return symUndefined;
    } else if (val.isPtr() || val.isCPtr()) {
        return objectToString(val);
    } else if (detail::primitiveToString(val, buf, kLen)) {
        return String::create(buf);
    } else {
        return null();
    }
}

}  // namespace libj
