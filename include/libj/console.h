// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_CONSOLE_H_
#define LIBJ_CONSOLE_H_

#include "libj/constant.h"

namespace libj {
namespace console {

enum Level {
    DEBUG,
    INFO,
    NORMAL,
    WARNING,
    ERROR,
    OFF,
};

enum Color {
    DEFAULT,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
};

Boolean log(const Value& val);
Boolean debug(const Value& val);
Boolean info(const Value& val);
Boolean warn(const Value& val);
Boolean error(const Value& val);

void log(const char* fmt, ...);
void debug(const char* fmt, ...);
void info(const char* fmt, ...);
void warn(const char* fmt, ...);
void error(const char* fmt, ...);

void printf(Level level, const char* fmt, ...);
void printv(Level level, const char* fmt,
    const Value& v0 = UNDEFINED, const Value& v1 = UNDEFINED,
    const Value& v2 = UNDEFINED, const Value& v3 = UNDEFINED,
    const Value& v4 = UNDEFINED, const Value& v5 = UNDEFINED,
    const Value& v6 = UNDEFINED, const Value& v7 = UNDEFINED,
    const Value& v8 = UNDEFINED, const Value& v9 = UNDEFINED);

void setLevel(Level level);
void setForegroundColor(Level level, Color color);
void setBackgroundColor(Level level, Color color);

}  // namespace console
}  // namespace libj

#endif  // LIBJ_CONSOLE_H_
