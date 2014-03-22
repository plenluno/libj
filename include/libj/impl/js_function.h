// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_JS_FUNCTION_H_
#define LIBJ_IMPL_JS_FUNCTION_H_

#define LIBJ_JS_FUNCTION_INSTANCEOF(ID) \
    (ID == libj::Type<libj::JsFunction>::id() || LIBJ_FUNCTION_INSTANCEOF(ID))

namespace libj {

inline Value JsFunction::operator()(ArrayList::Ptr args) {
    return operator()(JsArray::create(args));
}

inline Value JsFunction::call() {
    return operator()();
}

inline Value JsFunction::call(const Value& v1) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    return operator()(args);
}

inline Value JsFunction::call(const Value& v1, const Value& v2) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    return operator()(args);
}

inline Value JsFunction::call(
    const Value& v1, const Value& v2, const Value& v3) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    return operator()(args);
}

inline Value JsFunction::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    return operator()(args);
}

inline Value JsFunction::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    return operator()(args);
}

inline Value JsFunction::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    args->add(v6);
    return operator()(args);
}

inline Value JsFunction::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6,
    const Value& v7) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    args->add(v6);
    args->add(v7);
    return operator()(args);
}

inline Value JsFunction::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6,
    const Value& v7, const Value& v8) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    args->add(v6);
    args->add(v7);
    args->add(v8);
    return operator()(args);
}

inline Value JsFunction::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6,
    const Value& v7, const Value& v8, const Value& v9) {
    JsArray::Ptr args = JsArray::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    args->add(v6);
    args->add(v7);
    args->add(v8);
    args->add(v9);
    return operator()(args);
}

}  // namespace libj

#define LIBJ_JS_FUNCTION_TO_STRING(T) \
    virtual String::CPtr toString() const { \
        LIBJ_STATIC_CONST_STRING_DEF(strFunc, "function " #T "() {}") \
        return strFunc; \
    }

#define LIBJ_JS_FUNCTION_DEFS(T) \
    LIBJ_MUTABLE_DEFS(T, LIBJ_JS_FUNCTION) \
    LIBJ_JS_FUNCTION_TO_STRING(T)

#define LIBJ_JS_FUNCTION_TEMPLATE_DEFS(T) \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_JS_FUNCTION) \
    LIBJ_JS_FUNCTION_TO_STRING(T)

#endif  // LIBJ_IMPL_JS_FUNCTION_H_
