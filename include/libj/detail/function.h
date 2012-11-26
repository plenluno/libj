// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_FUNCTION_H_
#define LIBJ_DETAIL_FUNCTION_H_

namespace libj {

inline Value Function::call() {
    return operator()();
}

inline Value Function::call(const Value& v1) {
    ArrayList::Ptr args = ArrayList::create();
    args->add(v1);
    return operator()(args);
}

inline Value Function::call(const Value& v1, const Value& v2) {
    ArrayList::Ptr args = ArrayList::create();
    args->add(v1);
    args->add(v2);
    return operator()(args);
}

inline Value Function::call(
    const Value& v1, const Value& v2, const Value& v3) {
    ArrayList::Ptr args = ArrayList::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    return operator()(args);
}

inline Value Function::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4) {
    ArrayList::Ptr args = ArrayList::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    return operator()(args);
}

inline Value Function::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5) {
    ArrayList::Ptr args = ArrayList::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    return operator()(args);
}

inline Value Function::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6) {
    ArrayList::Ptr args = ArrayList::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    args->add(v6);
    return operator()(args);
}

inline Value Function::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6,
    const Value& v7) {
    ArrayList::Ptr args = ArrayList::create();
    args->add(v1);
    args->add(v2);
    args->add(v3);
    args->add(v4);
    args->add(v5);
    args->add(v6);
    args->add(v7);
    return operator()(args);
}

inline Value Function::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6,
    const Value& v7, const Value& v8) {
    ArrayList::Ptr args = ArrayList::create();
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

inline Value Function::call(
    const Value& v1, const Value& v2, const Value& v3,
    const Value& v4, const Value& v5, const Value& v6,
    const Value& v7, const Value& v8, const Value& v9) {
    ArrayList::Ptr args = ArrayList::create();
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

#endif  // LIBJ_DETAIL_FUNCTION_H_
