// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/json.h>
#include <libj/js_array.h>
#include <libj/js_object.h>
#include <libj/string_builder.h>
#include <libj/symbol.h>
#include <libj/glue/json.h>
#include <libj/detail/to_string.h>

#include <assert.h>

namespace libj {
namespace json {

Value parse(String::CPtr str) {
    return glue::json::parse(str);
}

static StringBuilder::Ptr stringify(
    const Value& val,
    StringBuilder::Ptr sb);

static StringBuilder::Ptr stringToJson(
    String::CPtr s,
    StringBuilder::Ptr sb) {
    sb->appendChar('"');
    for (Size i = 0; i < s->length(); i++) {
        Char c = s->charAt(i);
        switch (c) {
        case '\b':
            sb->appendCStr("\\b");
            break;
        case '\f':
            sb->appendCStr("\\f");
            break;
        case '\n':
            sb->appendCStr("\\n");
            break;
        case '\r':
            sb->appendCStr("\\r");
            break;
        case '\t':
            sb->appendCStr("\\t");
            break;
        case '"':
            sb->appendCStr("\\\"");
            break;
        case '\\':
            sb->appendCStr("\\\\");
            break;
        case '\0':
        case '\v':
            break;
        default:
            sb->appendChar(c);
        }
    }
    sb->appendChar('"');
    return sb;
}

static StringBuilder::Ptr mapToJson(
    Map::CPtr m,
    StringBuilder::Ptr sb) {
    typedef Map::Entry Entry;
    TypedSet<Entry::CPtr>::CPtr es = m->entrySet();
    TypedIterator<Entry::CPtr>::Ptr itr = es->iteratorTyped();
    Boolean first = true;
    sb->appendChar('{');
    while (itr->hasNext()) {
        Entry::CPtr e = itr->nextTyped();
        String::CPtr k = toCPtr<String>(e->getKey());
        Value v = e->getValue();
        if (k && !v.isUndefined()) {
            if (first) {
                first = false;
            } else {
                sb->appendChar(',');
            }
            stringToJson(k, sb);
            sb->appendChar(':');
            stringify(v, sb);
        }
    }
    sb->appendChar('}');
    return sb;
}

static StringBuilder::Ptr collectionToJson(
    Collection::CPtr c,
    StringBuilder::Ptr sb) {
    Iterator::Ptr itr = c->iterator();
    Boolean first = true;
    sb->appendChar('[');
    while (itr->hasNext()) {
        Value v = itr->next();
        if (first) {
            first = false;
        } else {
            sb->appendChar(',');
        }
        stringify(v, sb);
    }
    sb->appendChar(']');
    return sb;
}

static StringBuilder::Ptr stringify(
    const Value& val,
    StringBuilder::Ptr sb) {
    const Size kLen = 64;
    char buf[kLen];
    // 'undefined' only in collectionToJson
    if (val.isNull() || val.isUndefined()) {
        sb->appendCStr("null");
    } else if (val.is<String>()) {
        stringToJson(toCPtr<String>(val), sb);
    } else if (val.is<Map>()) {
        mapToJson(toCPtr<Map>(val), sb);
    } else if (val.is<Collection>()) {
        collectionToJson(toCPtr<Collection>(val), sb);
    } else if (val.is<Object>()) {
        sb->appendCStr("null");
    } else if (detail::primitiveToString(val, buf, kLen)) {
        sb->appendCStr(buf);
    } else {
        assert(false);
    }
    return sb;
}

String::CPtr stringify(const Value& val) {
    if (val.isUndefined()) {
        return String::null();
    } else {
        StringBuilder::Ptr sb = StringBuilder::create();
        return stringify(val, sb)->toString();
    }
}

}  // namespace json
}  // namespace libj
