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

static Level logLevel = LEVEL_DEBUG;

static inline Boolean isPrintable(Level level) {
    return level != LEVEL_OFF && logLevel <= level;
}

#ifdef LIBJ_USE_THREAD
    static detail::Mutex mutex;

    static inline Boolean lock() {
        return mutex.lock();
    }

    static inline Boolean unlock() {
        return mutex.unlock();
    }
#else
    static inline Boolean lock() {
        return true;
    }

    static inline Boolean unlock() {
        return true;
    }
#endif  // LIBJ_USE_THREAD

void setLevel(Level level) {
    lock();
    logLevel = level;
    unlock();
}

static Color foreDebug   = COLOR_DEFAULT;
static Color backDebug   = COLOR_DEFAULT;
static Color foreInfo    = COLOR_DEFAULT;
static Color backInfo    = COLOR_DEFAULT;
static Color foreNormal  = COLOR_DEFAULT;
static Color backNormal  = COLOR_DEFAULT;
static Color foreWarning = COLOR_DEFAULT;
static Color backWarning = COLOR_DEFAULT;
static Color foreError   = COLOR_DEFAULT;
static Color backError   = COLOR_DEFAULT;

static inline const char* fore(Color color) {
    switch (color) {
    case COLOR_DEFAULT:
        return "";
    case COLOR_BLACK:
        return "\033[30m";
    case COLOR_RED:
        return "\033[31m";
    case COLOR_GREEN:
        return "\033[32m";
    case COLOR_YELLOW:
        return "\033[33m";
    case COLOR_BLUE:
        return "\033[34m";
    case COLOR_MAGENTA:
        return "\033[35m";
    case COLOR_CYAN:
        return "\033[36m";
    case COLOR_WHITE:
        return "\033[37m";
    default:
        assert(false);
        return "";
    }
}

static inline const char* back(Color color) {
    switch (color) {
    case COLOR_DEFAULT:
        return "";
    case COLOR_BLACK:
        return "\033[40m";
    case COLOR_RED:
        return "\033[41m";
    case COLOR_GREEN:
        return "\033[42m";
    case COLOR_YELLOW:
        return "\033[43m";
    case COLOR_BLUE:
        return "\033[44m";
    case COLOR_MAGENTA:
        return "\033[45m";
    case COLOR_CYAN:
        return "\033[46m";
    case COLOR_WHITE:
        return "\033[47m";
    default:
        assert(false);
        return "";
    }
}

static inline const char* fore(Level level) {
    Color color;
    switch (level) {
    case LEVEL_DEBUG:
        color = foreDebug;
        break;
    case LEVEL_INFO:
        color = foreInfo;
        break;
    case LEVEL_NORMAL:
        color = foreNormal;
        break;
    case LEVEL_WARNING:
        color = foreWarning;
        break;
    case LEVEL_ERROR:
        color = foreError;
        break;
    default:  // case LEVEL_OFF:
        assert(false);
        color = COLOR_DEFAULT;
        break;
    }
    return fore(color);
}

static inline const char* back(Level level) {
    Color color;
    switch (level) {
    case LEVEL_DEBUG:
        color = backDebug;
        break;
    case LEVEL_INFO:
        color = backInfo;
        break;
    case LEVEL_NORMAL:
        color = backNormal;
        break;
    case LEVEL_WARNING:
        color = backWarning;
        break;
    case LEVEL_ERROR:
        color = backError;
        break;
    default:  // case LEVEL_OFF:
        assert(false);
        color = COLOR_DEFAULT;
        break;
    }
    return back(color);
}

static inline Color getForegroundColor(Level level) {
    switch (level) {
    case LEVEL_DEBUG:
        return foreDebug;
    case LEVEL_INFO:
        return foreInfo;
    case LEVEL_NORMAL:
        return foreNormal;
    case LEVEL_WARNING:
        return foreWarning;
    case LEVEL_ERROR:
        return foreError;
    default:  // case LEVEL_OFF:
        assert(false);
        return COLOR_DEFAULT;
    }
}

static inline Color getBackgroundColor(Level level) {
    switch (level) {
    case LEVEL_DEBUG:
        return backDebug;
    case LEVEL_INFO:
        return backInfo;
    case LEVEL_NORMAL:
        return backNormal;
    case LEVEL_WARNING:
        return backWarning;
    case LEVEL_ERROR:
        return backError;
    default:  // case LEVEL_OFF:
        assert(false);
        return COLOR_DEFAULT;
    }
}

void setForegroundColor(Level level, Color color) {
    lock();
    switch (level) {
    case LEVEL_DEBUG:
        foreDebug = color;
        break;
    case LEVEL_INFO:
        foreInfo = color;
        break;
    case LEVEL_NORMAL:
        foreNormal = color;
        break;
    case LEVEL_WARNING:
        foreWarning = color;
        break;
    case LEVEL_ERROR:
        foreError = color;
        break;
    default:  // case LEVEL_OFF:
        break;
    }
    unlock();
}

void setBackgroundColor(Level level, Color color) {
    lock();
    switch (level) {
    case LEVEL_DEBUG:
        backDebug = color;
        break;
    case LEVEL_INFO:
        backInfo = color;
        break;
    case LEVEL_NORMAL:
        backNormal = color;
        break;
    case LEVEL_WARNING:
        backWarning = color;
        break;
    case LEVEL_ERROR:
        backError = color;
        break;
    default:  // case LEVEL_OFF:
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
    if (getForegroundColor(LEVEL) != COLOR_DEFAULT) fprintf(OUT, "\033[0m"); \
    if (getBackgroundColor(LEVEL) != COLOR_DEFAULT) fprintf(OUT, "\033[0m");

void printf(Level level, const char* fmt, ...) {
    if (!isPrintable(level)) return;

    FILE* out = 0;
    switch (level) {
    case LEVEL_DEBUG:
    case LEVEL_INFO:
    case LEVEL_NORMAL:
        out = stdout;
        break;
    case LEVEL_WARNING:
    case LEVEL_ERROR:
        out = stderr;
        break;
    case LEVEL_OFF:
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
    LIBJ_PRINTLN(LEVEL_NORMAL, stdout, fmt);
    if (!fmt) { log(static_cast<Value>(0)); }
}

void debug(const char* fmt, ...) {
    LIBJ_PRINTLN(LEVEL_DEBUG, stdout, fmt);
    if (!fmt) { debug(static_cast<Value>(0)); }
}

void info(const char* fmt, ...) {
    LIBJ_PRINTLN(LEVEL_INFO, stdout, fmt);
    if (!fmt) { info(static_cast<Value>(0)); }
}

void warn(const char* fmt, ...) {
    LIBJ_PRINTLN(LEVEL_WARNING, stderr, fmt);
    if (!fmt) { warn(static_cast<Value>(0)); }
}

void error(const char* fmt, ...) {
    LIBJ_PRINTLN(LEVEL_ERROR, stderr, fmt);
    if (!fmt) { error(static_cast<Value>(0)); }
}

Boolean log(const Value& val) {
    if (val.isUndefined() || !isPrintable(LEVEL_NORMAL))
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
    if (val.isUndefined() || !isPrintable(LEVEL_DEBUG))
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
    if (val.isUndefined() || !isPrintable(LEVEL_INFO))
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
    if (val.isUndefined() || !isPrintable(LEVEL_WARNING))
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
    if (val.isUndefined() || !isPrintable(LEVEL_ERROR))
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
