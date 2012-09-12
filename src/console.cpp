// Copyright (c) 2012 Plenluno All rights reserved.

#include <iostream>

#include "libj/collection.h"
#include "libj/console.h"
#include "libj/json.h"
#include "libj/map.h"
#include "libj/string.h"

namespace libj {
namespace console {

void log(const char* s) {
    std::cout << s << std::endl;
}

void error(const char* s) {
    std::cerr << s << std::endl;
}

void write(const char* s) {
    std::cout << s;
}

void info(const char* s) {
    log(s);
}

void warn(const char* s) {
    error(s);
}

static String::CPtr toString(const Value& val) {
    String::CPtr s = String::null();
    if (val.instanceof(Type<Map>::id()) ||
        val.instanceof(Type<Collection>::id())) {
        s = json::stringify(val);
    } else {
        s = String::valueOf(val);
    }
    return s;
}

Boolean log(const Value& val) {
    String::CPtr s = toString(val);
    if (s) {
        log(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

Boolean error(const Value& val) {
    String::CPtr s = toString(val);
    if (s) {
        error(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

Boolean write(const Value& val) {
    String::CPtr s = toString(val);
    if (s) {
        write(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

Boolean info(const Value& val) {
    return log(val);
}

Boolean warn(const Value& val) {
    return error(val);
}

}  // namespace console
}  // namespace libj
