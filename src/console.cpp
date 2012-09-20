// Copyright (c) 2012 Plenluno All rights reserved.

#include <assert.h>
#include <iostream>

#include "libj/collection.h"
#include "libj/console.h"
#include "libj/json.h"
#include "libj/map.h"
#include "libj/string.h"

namespace libj {
namespace console {

void log(const char* str) {
    std::cout << str << std::endl;
}

void debug(const char* str) {
    log(str);
}

void info(const char* str) {
    log(str);
}

void warn(const char* str) {
    error(str);
}

void error(const char* str) {
    std::cerr << str << std::endl;
}

void write(const char* str, Level level) {
    switch (level) {
    case NORMAL:
    case DEBUG:
    case INFO:
        std::cout << str;
        break;
    case WARNING:
    case ERROR:
        std::cerr << str;
        break;
    default:
        assert(false);
    }
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

Boolean debug(const Value& val) {
    return log(val);
}

Boolean info(const Value& val) {
    return log(val);
}

Boolean warn(const Value& val) {
    return error(val);
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

Boolean write(const Value& val, Level level) {
    String::CPtr s = toString(val);
    if (s) {
        write(s->toStdString().c_str(), level);
        return true;
    } else {
        return false;
    }
}

}  // namespace console
}  // namespace libj
