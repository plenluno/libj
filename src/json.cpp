// Copyright (c) 2012 Plenluno All rights reserved.

#include <sstream>

#include "libj/error.h"
#include "json/json.h"
#include "libj/json.h"
#include "libj/js_array.h"
#include "libj/js_function.h"
#include "libj/js_object.h"
#include "libj/string_buffer.h"
#include "libj/symbol.h"

namespace libj {
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

static String::CPtr stringToJson(const Value& val) {
    String::CPtr s = toCPtr<String>(val);
    StringBuffer::Ptr result = StringBuffer::create();
    result->appendChar('"');
    for (Size i = 0; i < s->length(); i++) {
        Char c = s->charAt(i);
        switch (c) {
        case '\b':
            result->appendCStr("\\b");
            break;
        case '\t':
            result->appendCStr("\\t");
            break;
        case '\n':
            result->appendCStr("\\n");
            break;
        case '\r':
            result->appendCStr("\\r");
            break;
        case '"':
            result->appendCStr("\\\"");
            break;
        case '\\':
            result->appendCStr("\\\\");
            break;
        case '\0':
        case '\v':
            return String::null();
        default:
            result->appendChar(c);
        }
    }
    result->appendChar('"');
    return result->toString();
}

static String::CPtr mapToJson(const Value& val) {
    Map::CPtr m = toCPtr<Map>(val);
    Set::CPtr ks = m->keySet();
    Iterator::Ptr itr = ks->iterator();
    StringBuffer::Ptr result = StringBuffer::create();
    result->appendChar('{');
    while (itr->hasNext()) {
        Value k = itr->next();
        Value v = m->get(k);
        if (k.instanceof(Type<String>::id()) &&
            !v.isUndefined()) {
            if (result->length() > 1)
                result->appendChar(',');
            result->append(stringToJson(k));
            result->appendChar(':');
            result->append(json::stringify(v));
        }
    }
    result->appendChar('}');
    return result->toString();
}

static String::CPtr collectionToJson(const Value& val) {
    Collection::CPtr a = toCPtr<Collection>(val);
    Iterator::Ptr itr = a->iterator();
    StringBuffer::Ptr result = StringBuffer::create();
    result->appendChar('[');
    while (itr->hasNext()) {
        Value v = itr->next();
        if (result->length() > 1)
            result->appendChar(',');
        result->append(json::stringify(v));
    }
    result->appendChar(']');
    return result->toString();
}

String::CPtr stringify(const Value& val) {
    LIBJ_STATIC_SYMBOL_DEF(symNull, "null");

    if (val.isUndefined()) {
        return String::null();
    } else if (val.instanceof(Type<String>::id())) {
        return stringToJson(val);
    } else if (val.instanceof(Type<Map>::id())) {
        return mapToJson(val);
    } else if (val.instanceof(Type<Collection>::id())) {
        return collectionToJson(val);
    } else if (val.instanceof(Type<Object>::id())) {
        return symNull;
    } else {
        return String::valueOf(val);
    }
}

}  // namespace json
}  // namespace libj
