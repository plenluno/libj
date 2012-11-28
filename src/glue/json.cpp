// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/error.h>
#include <libj/js_array.h>
#include <libj/js_object.h>
#include <libj/glue/json.h>

#include <json/json.h>
#include <sstream>

namespace libj {
namespace glue {
namespace json {

static Json::Reader jsonReader;

static Value toLibjValue(const Json::Value& val) {
    if (val.isNull()) {
        return Object::null();
    } else if (val.isBool()) {
        return val.asBool();
    } else if (val.isInt()) {
        Long i = val.asInt();
        return i;
    } else if (val.isUInt()) {
        Long u = val.asUInt();
        return u;
    } else if (val.isDouble()) {
        return val.asDouble();
    } else if (val.isString()) {
        return String::create(val.asCString(), String::UTF8);
    } else if (val.isArray()) {
        JsArray::Ptr a = JsArray::create();
        Size len = val.size();
        for (Size i = 0; i < len; i++) {
            a->add(toLibjValue(val[static_cast<Json::UInt>(i)]));
        }
        return a;
    } else if (val.isObject()) {
        JsObject::Ptr jo = JsObject::create();
        Json::Value::Members ms = val.getMemberNames();
        Size len = ms.size();
        for (Size i = 0; i < len; i++) {
            String::CPtr k = String::create(ms[i].c_str());
            Value v = toLibjValue(val[ms[i]]);
            jo->put(k, v);
        }
        return jo;
    } else {
        return UNDEFINED;
    }
}

Value parse(String::CPtr str) {
    Json::Value root;
    std::istringstream is(str->toStdString());
    if (jsonReader.parse(is, root))
        return toLibjValue(root);
    else
        return Error::create(Error::ILLEGAL_ARGUMENT);
}

}  // namespace json
}  // namespace glue
}  // namespace libj
