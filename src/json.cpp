// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/json.h>
#include <libj/js_array.h>
#include <libj/js_object.h>
#include <libj/string_buffer.h>
#include <libj/symbol.h>
#include <libj/glue/json.h>

namespace libj {
namespace json {

Value parse(String::CPtr str) {
    return glue::json::parse(str);
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
