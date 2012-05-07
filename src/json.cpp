// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/json.h"
#include "libj/array_list.h"
#include "libj/error.h"
#include "libj/map.h"
#include "libj/null.h"
#include "libj/string.h"

namespace libj {
namespace json {

Value parse(Type<String>::Cptr str) {
    // TODO: implement
    return 0;
}

static Type<String>::Cptr JSON_NULL = String::create("null");
static Type<String>::Cptr JSON_TRUE = String::create("true");
static Type<String>::Cptr JSON_FALSE = String::create("false");
static Type<String>::Cptr JSON_COLON = String::create(":");
static Type<String>::Cptr JSON_COMMA = String::create(",");
static Type<String>::Cptr JSON_DQUOTE = String::create("\"");
static Type<String>::Cptr JSON_LBRACKET = String::create("[");
static Type<String>::Cptr JSON_RBRACKET = String::create("]");
static Type<String>::Cptr JSON_LBRACE = String::create("{");
static Type<String>::Cptr JSON_RBRACE = String::create("}");


static Type<String>::Cptr booleanToJson(Value val) {
    Boolean b;
    to<Boolean>(val, &b);
    return b ? JSON_TRUE : JSON_FALSE;
}

static Type<String>::Cptr byteToJson(Value val) {
    Byte b;
    to<Byte>(val, &b);
    const Size len = (8 / 3) + 3;
    char s[len];
    snprintf(s, len, "%d", b);
    return String::create(s);
}

static Type<String>::Cptr shortToJson(Value val) {
    Short sh;
    to<Short>(val, &sh);
    const Size len = (16 / 3) + 3;
    char s[len];
    snprintf(s, len, "%d", sh);
    return String::create(s);
}

static Type<String>::Cptr intToJson(Value val) {
    Int i;
    to<Int>(val, &i);
    const Size len = (32 / 3) + 3;
    char s[len];
    snprintf(s, len, "%d", i);
    return String::create(s);
}

static Type<String>::Cptr longToJson(Value val) {
    Long l;
    to<Long>(val, &l);
    const Size len = (64 / 3) + 3;
    char s[len];
    snprintf(s, len, "%lld", l);
    return String::create(s);
}

static Type<String>::Cptr floatToJson(Value val) {
    Float f;
    to<Float>(val, &f);
    const Size len = (32 / 3) + 5;
    char s[len];
    snprintf(s, len, "%f", f);
    return String::create(s);
}

static Type<String>::Cptr doubleToJson(Value val) {
    Double d;
    to<Double>(val, &d);
    const Size len = (64 / 3) + 5;
    char s[len];
    snprintf(s, len, "%lf", d);
    return String::create(s);
}

static Type<String>::Cptr stringToJson(Value val) {
    Type<String>::Cptr s = toCptr<String>(val);
    Type<String>::Cptr result = JSON_DQUOTE->concat(s)->concat(JSON_DQUOTE);
    return result;
}

static Type<String>::Cptr mapToJson(Value val) {
    Type<Map>::Cptr m = toCptr<Map>(val);
    Type<Set>::Cptr ks = m->keySet();
    Type<Iterator>::Ptr itr = ks->iterator();
    Type<String>::Cptr result = JSON_LBRACE;
    while (itr->hasNext()) {
        Value v = itr->next();
        if (v.instanceOf(Type<String>::id())) {
            if (result->length() > 1)
                result = result->concat(JSON_COMMA);
            result = result
                ->concat(stringToJson(v))
                ->concat(JSON_COLON)
                ->concat(json::stringify(m->get(v)));
        }
    }
    result = result->concat(JSON_RBRACE);
    return result;
}

static Type<String>::Cptr collectionToJson(Value val) {
    Type<Collection>::Cptr a = toCptr<Collection>(val);
    Type<Iterator>::Ptr itr = a->iterator();
    Type<String>::Cptr result = JSON_LBRACKET;
    while (itr->hasNext()) {
        Value v = itr->next();
        if (result->length() > 1)
            result = result->concat(JSON_COMMA);
        result = result->concat(json::stringify(v));
    }
    result = result->concat(JSON_RBRACKET);
    return result;
}

Type<String>::Cptr stringify(Value val) {
    if (val.instanceOf(Type<Null>::id())) {
        return JSON_NULL;
    } else if (val.type() == Type<Boolean>::id()) {
        return booleanToJson(val);
    } else if (val.type() == Type<Byte>::id()) {
        return byteToJson(val);
    } else if (val.type() == Type<Short>::id()) {
        return shortToJson(val);
    } else if (val.type() == Type<Int>::id()) {
        return intToJson(val);
    } else if (val.type() == Type<Long>::id()) {
        return longToJson(val);
    } else if (val.type() == Type<Float>::id()) {
        return floatToJson(val);
    } else if (val.type() == Type<Double>::id()) {
        return doubleToJson(val);
    } else if (val.instanceOf(Type<String>::id())) {
        return stringToJson(val);
    } else if (val.instanceOf(Type<Map>::id())) {
        return mapToJson(val);
    } else if (val.instanceOf(Type<Collection>::id())) {
        return collectionToJson(val);
    } else {
        return JSON_NULL;
    }
}

}  // namespace json
}  // namespace libj
