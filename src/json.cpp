// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/json.h"
#include "libj/array_list.h"
#include "libj/map.h"
#include "libj/string_buffer.h"

namespace libj {
namespace json {

Value parse(String::CPtr str) {
    // TODO: implement
    return 0;
}

static String::CPtr JSON_NULL = String::create("null");
static String::CPtr JSON_COLON = String::create(":");
static String::CPtr JSON_COMMA = String::create(",");
static String::CPtr JSON_DQUOTE = String::create("\"");
static String::CPtr JSON_LBRACKET = String::create("[");
static String::CPtr JSON_RBRACKET = String::create("]");
static String::CPtr JSON_LBRACE = String::create("{");
static String::CPtr JSON_RBRACE = String::create("}");

static String::CPtr stringToJson(const Value& val) {
    String::CPtr s = toCPtr<String>(val);
    String::CPtr result = JSON_DQUOTE->concat(s)->concat(JSON_DQUOTE);
    return result;
}

static String::CPtr mapToJson(const Value& val) {
    Map::CPtr m = toCPtr<Map>(val);
    Set::CPtr ks = m->keySet();
    Iterator::Ptr itr = ks->iterator();
    StringBuffer::Ptr result = StringBuffer::create();
    result->append(JSON_LBRACE);
    while (itr->hasNext()) {
        Value v = itr->next();
        if (v.instanceOf(Type<String>::id())) {
            if (result->length() > 1)
                result->append(JSON_COMMA);
            result->append(stringToJson(v));
            result->append(JSON_COLON);
            result->append(json::stringify(m->get(v)));
        }
    }
    result->append(JSON_RBRACE);
    return result->toString();
}

static String::CPtr collectionToJson(const Value& val) {
    Collection::CPtr a = toCPtr<Collection>(val);
    Iterator::Ptr itr = a->iterator();
    StringBuffer::Ptr result = StringBuffer::create();
    result->append(JSON_LBRACKET);
    while (itr->hasNext()) {
        Value v = itr->next();
        if (result->length() > 1)
            result->append(JSON_COMMA);
        result->append(json::stringify(v));
    }
    result->append(JSON_RBRACKET);
    return result->toString();
}

String::CPtr stringify(const Value& val) {
    if (val.instanceOf(Type<String>::id())) {
        return stringToJson(val);
    } else if (val.instanceOf(Type<Map>::id())) {
        return mapToJson(val);
    } else if (val.instanceOf(Type<Collection>::id())) {
        return collectionToJson(val);
    } else if (val.instanceOf(Type<Object>::id())) {
        return JSON_NULL;
    } else {
        return String::valueOf(val);
    }
}

}  // namespace json
}  // namespace libj
