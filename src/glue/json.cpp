// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/error.h>
#include <libj/endian.h>
#include <libj/js_array.h>
#include <libj/js_object.h>
#include <libj/glue/json.h>

#include <math.h>
#include <rapidjson/document.h>

#include <string>
#include <sstream>

namespace libj {
namespace glue {
namespace json {

static Value doubleToValue(Double d) {
    static const Double JSON_INTEGER_MAX = +9007199254740991.0;
    static const Double JSON_INTEGER_MIN = -9007199254740991.0;

    Double intpart;
    if (modf(d, &intpart) == 0.0 &&
        intpart <= JSON_INTEGER_MAX &&
        intpart >= JSON_INTEGER_MIN) {
        Long l = static_cast<Long>(intpart);
        return l;
    } else {
        return d;
    }
}

static Value longToValue(Long l) {
    static const Long JSON_INTEGER_MAX = +9007199254740991;
    static const Long JSON_INTEGER_MIN = -9007199254740991;

    if (l <= JSON_INTEGER_MAX && l >= JSON_INTEGER_MIN) {
        return l;
    } else {
        return static_cast<Double>(l);
    }
}

static Boolean isBigEndian() {
    static Endian e = endian();
    return e == BIG;
}

static String::CPtr createString(const Char* s) {
#ifdef LIBJ_USE_UTF32
    if (isBigEndian()) {
        return String::create(s, String::UTF32BE);
    } else {
        return String::create(s, String::UTF32LE);
    }
#else
    if (isBigEndian()) {
        return String::create(s, String::UTF16BE);
    } else {
        return String::create(s, String::UTF16LE);
    }
#endif
}

#ifdef LIBJ_USE_UTF32
typedef rapidjson::UTF32<Char> JsonEnc;
#else
typedef rapidjson::UTF16<Char> JsonEnc;
#endif

typedef rapidjson::GenericValue<JsonEnc> JsonValue;
typedef rapidjson::GenericDocument<JsonEnc> Document;

static Value convert(const JsonValue& val) {
    if (val.IsNull()) {
        return Object::null();
    } else if (val.IsBool()) {
        return val.GetBool();
    } else if (val.IsInt64()) {
        return longToValue(val.GetInt64());
    } else if (val.IsDouble()) {
        return doubleToValue(val.GetDouble());
    } else if (val.IsString()) {
        return createString(val.GetString());
    } else if (val.IsArray()) {
        JsArray::Ptr ja = JsArray::create();
        for (JsonValue::ConstValueIterator itr = val.Begin();
             itr != val.End();
             ++itr) {
            ja->add(convert(*itr));
        }
        return ja;
    } else if (val.IsObject()) {
        JsObject::Ptr jo = JsObject::create();
        for (JsonValue::ConstMemberIterator itr = val.MemberBegin();
             itr != val.MemberEnd();
             ++itr) {
            String::CPtr k = createString(itr->name.GetString());
            Value v = convert(itr->value);
            jo->put(k, v);
        }
        return jo;
    } else {
        return UNDEFINED;
    }
}

Value parse(String::CPtr str) {
    if (!str) return Error::create(Error::ILLEGAL_ARGUMENT);

    Document doc;
    if (doc.Parse<0>(str->data()).HasParseError()) {
        return Error::create(Error::ILLEGAL_ARGUMENT);
    } else {
        return convert(doc);
    }
}

}  // namespace json
}  // namespace glue
}  // namespace libj
