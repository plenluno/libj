// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_CONSOLE_H_
#define LIBJ_CONSOLE_H_

#include "libj/value.h"

namespace libj {
namespace console {

enum Level {
    NORMAL,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

void log(const char* str);
void debug(const char* str);
void info(const char* str);
void warn(const char* str);
void error(const char* str);
void write(const char* str, Level level = NORMAL);

Boolean log(const Value& val);
Boolean debug(const Value& val);
Boolean info(const Value& val);
Boolean warn(const Value& val);
Boolean error(const Value& val);
Boolean write(const Value& val, Level level = NORMAL);

}  // namespace console
}  // namespace libj

#endif  // LIBJ_CONSOLE_H_
