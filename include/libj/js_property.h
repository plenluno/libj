// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_PROPERTY_H_
#define LIBJ_JS_PROPERTY_H_

#include "libj/js_object.h"

#define LIBJ_JS_PROPERTY_DECL \
public: \
    virtual Boolean hasProperty(const Value& name) const = 0; \
    virtual Value getProperty(const Value& name) const = 0; \
    virtual Value setProperty(const Value& name, const Value& val) = 0; \
    virtual Value deleteProperty(const Value& name) = 0;

#define LIBJ_JS_PROPERTY_IMPL(JO) \
public: \
    Boolean hasProperty(const Value& name) const { \
        return JO->hasProperty(name); \
    } \
    Value getProperty(const Value& name) const { \
        return JO->getProperty(name); \
    } \
    Value setProperty(const Value& name, const Value& val) { \
        return JO->setProperty(name, val); \
    } \
    Value deleteProperty(const Value& name) { \
        return JO->deleteProperty(name); \
    }

#define LIBJ_JS_PROPERTY_MIX(T) \
private: \
    JsObject::Ptr jo_; \
public: \
    T() : jo_(JsObject::create()) {} \
    LIBJ_JS_PROPERTY_IMPL(jo_)


#endif  // LIBJ_JS_PROPERTY_H_
