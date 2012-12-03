// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/error.h>
#include <libj/js_array.h>
#include <libj/js_object.h>
#include <libj/glue/json.h>

#ifdef LIBJ_USE_JSONCPP
    #include <json/json.h>
#else
    #include <picojson.h>
#endif
#include <math.h>
#include <string>
#include <sstream>

namespace libj {
namespace glue {
namespace json {

#ifdef LIBJ_USE_JSONCPP

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
        Double d = val.asDouble();
        Double intpart;
        if (modf(d, &intpart) == 0.0) {
            Long l = static_cast<Long>(intpart);
            return l;
        } else {
            return d;
        }
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
    if (!str) return Error::create(Error::ILLEGAL_ARGUMENT);

    Json::Value root;
    std::istringstream is(str->toStdString());
    if (jsonReader.parse(is, root)) {
        return toLibjValue(root);
    } else {
        return Error::create(Error::ILLEGAL_ARGUMENT);
    }
}

#else

static Value toLibjValue(const picojson::value& val) {
    if (val.is<picojson::null>()) {
        return Object::null();
    } else if (val.is<Boolean>()) {
        return val.get<Boolean>();
    } else if (val.is<Double>()) {
        Double d = val.get<Double>();
        Double intpart;
        if (modf(d, &intpart) == 0.0) {
            Long l = static_cast<Long>(intpart);
            return l;
        } else {
            return d;
        }
    } else if (val.is<std::string>()) {
        std::string s = val.get<std::string>();
        return String::create(s.c_str(), String::UTF8);
    } else if (val.is<picojson::array>()) {
        picojson::array pa = val.get<picojson::array>();
        JsArray::Ptr ja = JsArray::create();
        for (picojson::array::const_iterator i = pa.begin();
             i != pa.end();
             ++i) {
            ja->add(toLibjValue(*i));
        }
        return ja;
    } else if (val.is<picojson::object>()) {
        picojson::object po = val.get<picojson::object>();
        JsObject::Ptr jo = JsObject::create();
        for (picojson::object::const_iterator i = po.begin();
             i != po.end();
             ++i) {
            String::CPtr k = String::create(i->first.c_str());
            Value v = toLibjValue(i->second);
            jo->put(k, v);
        }
        return jo;
    } else {
        return UNDEFINED;
    }
}

Value parse(String::CPtr str) {
    if (!str) return Error::create(Error::ILLEGAL_ARGUMENT);

    picojson::value v;
    std::string s = str->toStdString();
    const char* cstr = s.c_str();
    std::string err;
    picojson::parse(v, cstr, cstr + s.length(), &err);
    if (err.empty()) {
        return toLibjValue(v);
    } else {
        return Error::create(Error::ILLEGAL_ARGUMENT);
    }
}

#endif

}  // namespace json
}  // namespace glue
}  // namespace libj
