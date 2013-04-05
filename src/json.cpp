// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/json.h>
#include <libj/js_array.h>
#include <libj/js_object.h>
#include <libj/string_buffer.h>
#include <libj/symbol.h>
#include <libj/glue/json.h>
#include <libj/detail/util.h>

#include <assert.h>

namespace libj {
namespace json {

Value parse(String::CPtr str) {
    return glue::json::parse(str);
}

static StringBuffer::Ptr stringify(
    StringBuffer::Ptr result,
    const Value& val);

static StringBuffer::Ptr stringToJson(
    StringBuffer::Ptr result,
    String::CPtr s) {
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
            break;
        default:
            result->appendChar(c);
        }
    }
    result->appendChar('"');
    return result;
}

static StringBuffer::Ptr mapToJson(
    StringBuffer::Ptr result,
    Map::CPtr m) {
    Set::CPtr ks = m->keySet();
    Iterator::Ptr itr = ks->iterator();
    Boolean first = true;
    result->appendChar('{');
    while (itr->hasNext()) {
        String::CPtr k = toCPtr<String>(itr->next());
        Value v = m->get(k);
        if (k && !v.isUndefined()) {
            if (first) {
                first = false;
            } else {
                result->appendChar(',');
            }
            stringToJson(result, k);
            result->appendChar(':');
            stringify(result, v);
        }
    }
    result->appendChar('}');
    return result;
}

static StringBuffer::Ptr collectionToJson(
    StringBuffer::Ptr result,
    Collection::CPtr c) {
    Iterator::Ptr itr = c->iterator();
    Boolean first = true;
    result->appendChar('[');
    while (itr->hasNext()) {
        Value v = itr->next();
        if (first) {
            first = false;
        } else {
            result->appendChar(',');
        }
        stringify(result, v);
    }
    result->appendChar(']');
    return result;
}

static StringBuffer::Ptr stringify(
    StringBuffer::Ptr result,
    const Value& val) {
    const Size kLen = 64;
    char buf[kLen];
    // 'undefined' only in collectionToJson
    if (val.isNull() || val.isUndefined()) {
        result->appendCStr("null");
    } else if (val.instanceof(Type<String>::id())) {
        stringToJson(result, toCPtr<String>(val));
    } else if (val.instanceof(Type<Map>::id())) {
        mapToJson(result, toCPtr<Map>(val));
    } else if (val.instanceof(Type<Collection>::id())) {
        collectionToJson(result, toCPtr<Collection>(val));
    } else if (val.instanceof(Type<Object>::id())) {
        result->appendCStr("null");
    } else if (detail::primitiveToString(val, buf, kLen)) {
        result->appendCStr(buf);
    } else {
        assert(false);
    }
    return result;
}

String::CPtr stringify(const Value& val) {
    if (val.isUndefined()) {
        return String::null();
    } else {
        StringBuffer::Ptr result = StringBuffer::create();
        return stringify(result, val)->toString();
    }
}

}  // namespace json
}  // namespace libj
