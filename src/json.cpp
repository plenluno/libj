// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/json.h"
#include "libj/array_list.h"
#include "libj/map.h"
#include "libj/string_buffer.h"

namespace libj {
namespace json {

Value parse(Type<String>::Cptr str) {
    // TODO: implement
    return 0;
}

static Type<String>::Cptr JSON_NULL = String::create("null");
static Type<String>::Cptr JSON_COLON = String::create(":");
static Type<String>::Cptr JSON_COMMA = String::create(",");
static Type<String>::Cptr JSON_DQUOTE = String::create("\"");
static Type<String>::Cptr JSON_LBRACKET = String::create("[");
static Type<String>::Cptr JSON_RBRACKET = String::create("]");
static Type<String>::Cptr JSON_LBRACE = String::create("{");
static Type<String>::Cptr JSON_RBRACE = String::create("}");

static Type<String>::Cptr stringToJson(const Value& val) {
    Type<String>::Cptr s = toCptr<String>(val);
    Type<String>::Cptr result = JSON_DQUOTE->concat(s)->concat(JSON_DQUOTE);
    return result;
}

static Type<String>::Cptr mapToJson(const Value& val) {
    Type<Map>::Cptr m = toCptr<Map>(val);
    Type<Set>::Cptr ks = m->keySet();
    Type<Iterator>::Ptr itr = ks->iterator();
    Type<StringBuffer>::Ptr result = StringBuffer::create();
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

static Type<String>::Cptr collectionToJson(const Value& val) {
    Type<Collection>::Cptr a = toCptr<Collection>(val);
    Type<Iterator>::Ptr itr = a->iterator();
    Type<StringBuffer>::Ptr result = StringBuffer::create();
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

Type<String>::Cptr stringify(const Value& val) {
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
