// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/collection.h>
#include <libj/console.h>
#include <libj/json.h>
#include <libj/map.h>
#include <libj/string.h>
#include <libj/detail/mutex.h>

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>

#pragma GCC diagnostic ignored "-Wformat-security"

namespace libj {
namespace console {

static Level logLevel = DEBUG;

static Boolean isPrintable(Level level) {
    return level != OFF && logLevel <= level;
}

#ifdef LIBJ_USE_THREAD
    static detail::Mutex mutex;

    static Boolean lock() {
        return mutex.lock();
    }

    static Boolean unlock() {
        return mutex.unlock();
    }
#else
    static Boolean lock() {
        return true;
    }

    static Boolean unlock() {
        return true;
    }
#endif  // LIBJ_USE_THREAD

void setLevel(Level level) {
    lock();
    logLevel = level;
    unlock();
}

static Color foreDebug   = DEFAULT;
static Color backDebug   = DEFAULT;
static Color foreInfo    = DEFAULT;
static Color backInfo    = DEFAULT;
static Color foreNormal  = DEFAULT;
static Color backNormal  = DEFAULT;
static Color foreWarning = DEFAULT;
static Color backWarning = DEFAULT;
static Color foreError   = DEFAULT;
static Color backError   = DEFAULT;

static const char* fore(Color color) {
    switch (color) {
    case DEFAULT:
        return "";
    case BLACK:
        return "\033[30m";
    case RED:
        return "\033[31m";
    case GREEN:
        return "\033[32m";
    case YELLOW:
        return "\033[33m";
    case BLUE:
        return "\033[34m";
    case MAGENTA:
        return "\033[35m";
    case CYAN:
        return "\033[36m";
    case WHITE:
        return "\033[37m";
    default:
        assert(false);
        return "";
    }
}

static const char* back(Color color) {
    switch (color) {
    case DEFAULT:
        return "";
    case BLACK:
        return "\033[40m";
    case RED:
        return "\033[41m";
    case GREEN:
        return "\033[42m";
    case YELLOW:
        return "\033[43m";
    case BLUE:
        return "\033[44m";
    case MAGENTA:
        return "\033[45m";
    case CYAN:
        return "\033[46m";
    case WHITE:
        return "\033[47m";
    default:
        assert(false);
        return "";
    }
}

static const char* fore(Level level) {
    Color color;
    switch (level) {
    case DEBUG:
        color = foreDebug;
        break;
    case INFO:
        color = foreInfo;
        break;
    case NORMAL:
        color = foreNormal;
        break;
    case WARNING:
        color = foreWarning;
        break;
    case ERROR:
        color = foreError;
        break;
    case OFF:
        color = DEFAULT;
        break;
    }
    return fore(color);
}

static const char* back(Level level) {
    Color color;
    switch (level) {
    case DEBUG:
        color = backDebug;
        break;
    case INFO:
        color = backInfo;
        break;
    case NORMAL:
        color = backNormal;
        break;
    case WARNING:
        color = backWarning;
        break;
    case ERROR:
        color = backError;
        break;
    case OFF:
        color = DEFAULT;
        break;
    }
    return back(color);
}

void setForegroundColor(Level level, Color color) {
    lock();
    switch (level) {
    case DEBUG:
        foreDebug = color;
        break;
    case INFO:
        foreInfo = color;
        break;
    case NORMAL:
        foreNormal = color;
        break;
    case WARNING:
        foreWarning = color;
        break;
    case ERROR:
        foreError = color;
        break;
    case OFF:
        break;
    }
    unlock();
}

void setBackgroundColor(Level level, Color color) {
    lock();
    switch (level) {
    case DEBUG:
        backDebug = color;
        break;
    case INFO:
        backInfo = color;
        break;
    case NORMAL:
        backNormal = color;
        break;
    case WARNING:
        backWarning = color;
        break;
    case ERROR:
        backError = color;
        break;
    case OFF:
        break;
    }
    unlock();
}

#define LIBJ_VFPRINTF(LEVEL, OUT, FMT) \
    va_list argp; \
    va_start(argp, FMT); \
    fprintf(OUT, fore(LEVEL)); \
    fprintf(OUT, back(LEVEL)); \
    vfprintf(OUT, FMT, argp); \
    fprintf(OUT, "\033[0m"); \
    fprintf(OUT, "\033[0m");

void printf(Level level, const char* fmt, ...) {
    if (!isPrintable(level)) return;

    FILE* out = 0;
    switch (level) {
    case DEBUG:
    case INFO:
    case NORMAL:
        out = stdout;
        break;
    case WARNING:
    case ERROR:
        out = stderr;
        break;
    case OFF:
        assert(false);
    }

    lock();
    LIBJ_VFPRINTF(level, out, fmt);
    unlock();
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

void printv(
    Level level, const char* fmt,
    const Value& v0, const Value& v1,
    const Value& v2, const Value& v3,
    const Value& v4, const Value& v5,
    const Value& v6, const Value& v7,
    const Value& v8, const Value& v9) {
    if (!isPrintable(level)) return;

    const Size kMax = 10;
    std::string format(fmt);
    Size count = 0;
    size_t pos = 0;
    while (1) {
        pos = format.find("%v", pos);
        if (pos == std::string::npos) {
            break;
        } else {
            format.replace(pos, 2, "%s");
            count++;
        }
    }

    String::CPtr s[kMax];
    s[0] = toString(v0);
    s[1] = toString(v1);
    s[2] = toString(v2);
    s[3] = toString(v3);
    s[4] = toString(v4);
    s[5] = toString(v5);
    s[6] = toString(v6);
    s[7] = toString(v7);
    s[8] = toString(v8);
    s[9] = toString(v9);
    for (Size i = count; i < kMax; i++) {
        format += "%s";
        s[i] = String::null();
    }

    printf(level, format.c_str(),
        s[0] ? s[0]->toStdString().c_str() : "",
        s[1] ? s[1]->toStdString().c_str() : "",
        s[2] ? s[2]->toStdString().c_str() : "",
        s[3] ? s[3]->toStdString().c_str() : "",
        s[4] ? s[4]->toStdString().c_str() : "",
        s[5] ? s[5]->toStdString().c_str() : "",
        s[6] ? s[6]->toStdString().c_str() : "",
        s[7] ? s[7]->toStdString().c_str() : "",
        s[8] ? s[8]->toStdString().c_str() : "",
        s[9] ? s[9]->toStdString().c_str() : "");
}

#define LIBJ_PRINTLN(LEVEL, OUT, FMT) \
    if (!isPrintable(LEVEL)) return; \
    if (FMT) { \
        lock(); \
        LIBJ_VFPRINTF(LEVEL, OUT, FMT) \
        fprintf(OUT, "\n"); \
        unlock(); \
        return; \
    }

void log(const char* fmt, ...) {
    LIBJ_PRINTLN(NORMAL, stdout, fmt);
    if (!fmt) { log(static_cast<Value>(0)); }
}

void debug(const char* fmt, ...) {
    LIBJ_PRINTLN(DEBUG, stdout, fmt);
    if (!fmt) { debug(static_cast<Value>(0)); }
}

void info(const char* fmt, ...) {
    LIBJ_PRINTLN(INFO, stdout, fmt);
    if (!fmt) { info(static_cast<Value>(0)); }
}

void warn(const char* fmt, ...) {
    LIBJ_PRINTLN(WARNING, stderr, fmt);
    if (!fmt) { warn(static_cast<Value>(0)); }
}

void error(const char* fmt, ...) {
    LIBJ_PRINTLN(ERROR, stderr, fmt);
    if (!fmt) { error(static_cast<Value>(0)); }
}

Boolean log(const Value& val) {
    if (val.isUndefined() || !isPrintable(NORMAL))
        return false;

    String::CPtr s = toString(val);
    if (s) {
        log(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

Boolean debug(const Value& val) {
    if (val.isUndefined() || !isPrintable(DEBUG))
        return false;

    String::CPtr s = toString(val);
    if (s) {
        debug(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

Boolean info(const Value& val) {
    if (val.isUndefined() || !isPrintable(INFO))
        return false;

    String::CPtr s = toString(val);
    if (s) {
        info(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

Boolean warn(const Value& val) {
    if (val.isUndefined() || !isPrintable(WARNING))
        return false;

    String::CPtr s = toString(val);
    if (s) {
        warn(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

Boolean error(const Value& val) {
    if (val.isUndefined() || !isPrintable(ERROR))
        return false;

    String::CPtr s = toString(val);
    if (s) {
        error(s->toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

}  // namespace console
}  // namespace libj
