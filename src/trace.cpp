// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/trace.h>
#include <libj/glue/regexp.h>

#include <assert.h>
#include <cxxabi.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <vector>

#ifdef LIBJ_TRACE

static int depth = 0;

static bool isEnabled = false;
static bool wasEnabled = false;

static void resume() {
    isEnabled = wasEnabled;
}

static void stop() {
    wasEnabled = isEnabled;
    isEnabled = false;
}

static void* convert(const char* s, int len) {
    switch (libj::glue::RegExp::encoding()) {
    case libj::glue::RegExp::UTF8:
        {
            uint8_t* d = static_cast<uint8_t*>(malloc(len + 1));
            for (int i = 0; i < len; i++) {
                d[i] = s[i];
            }
            d[len] = 0;
            return d;
        }
    case libj::glue::RegExp::UTF16:
        {
            uint16_t* d = static_cast<uint16_t*>(malloc((len + 1) << 1));
            for (int i = 0; i < len; i++) {
                d[i] = s[i];
            }
            d[len] = 0;
            return d;
        }
    case libj::glue::RegExp::UTF32:
        {
            uint32_t* d = static_cast<uint32_t*>(malloc((len + 1) << 2));
            for (int i = 0; i < len; i++) {
                d[i] = s[i];
            }
            d[len] = 0;
            return d;
        }
    default:
        assert(false);
        return NULL;
    }
}

static libj::glue::RegExp* createRegExp(const char* pattern) {
    if (!isEnabled || !pattern) {
        return NULL;
    } else {
        int len = strlen(pattern);
        void* pat = convert(pattern, len);
        libj::glue::RegExp* re = libj::glue::RegExp::create(pat, len, 0);
        free(pat);
        return re;
    }
}

static std::vector<libj::glue::RegExp*>* whiteList() {
    static std::vector<libj::glue::RegExp*> patterns;
    return &patterns;
}

static std::vector<libj::glue::RegExp*>* blackList() {
    static std::vector<libj::glue::RegExp*> patterns;
    return &patterns;
}

static void clear() {
    std::vector<libj::glue::RegExp*>::iterator itr;
    for (itr = whiteList()->begin(); itr != whiteList()->end(); ++itr) {
        delete *itr;
    }
    whiteList()->clear();

    for (itr = blackList()->begin(); itr != blackList()->end(); ++itr) {
        delete *itr;
    }
    blackList()->clear();
}

static bool isPrintable(const char* funcName) {
    if (!funcName) return false;

    int len = strlen(funcName);
    void* name = convert(funcName, len);
    std::vector<int> captures;
    std::vector<libj::glue::RegExp*>::const_iterator itr;

    for (itr = blackList()->begin(); itr != blackList()->end(); ++itr) {
        if ((*itr)->execute(name, len, 0, captures)) {
            free(name);
            return false;
        }
    }

    for (itr = whiteList()->begin(); itr != whiteList()->end(); ++itr) {
        if ((*itr)->execute(name, len, 0, captures)) {
            free(name);
            return true;
        }
    }

    free(name);
    return false;
}

static char* addrToName(void* address) {
    Dl_info dli;
    if (dladdr(address, &dli)) {
        int status;
        return abi::__cxa_demangle(dli.dli_sname, 0, 0, &status);
    } else {
        return NULL;
    }
}

extern "C" {
    void __cyg_profile_func_enter(void* funcAddress, void* callSite);
    void __cyg_profile_func_exit(void* funcAddress, void* callSite);
}

void __cyg_profile_func_enter(void* funcAddress, void* callSite) {
    if (!isEnabled || whiteList()->empty()) return;

    stop();

    char* funcName = addrToName(funcAddress);
    if (isPrintable(funcName)) {
        depth++;
        printf("[LIBJ TRACE] enter: [%d: %s]\n", depth, funcName);
    }
    free(funcName);

    resume();
}

void __cyg_profile_func_exit(void* funcAddress, void* callSite) {
    if (!isEnabled || whiteList()->empty()) return;

    stop();

    char* funcName = addrToName(funcAddress);
    if (isPrintable(funcName)) {
        printf("[LIBJ TRACE] exit:  [%d: %s]\n", depth, funcName);
        depth--;
    }
    free(funcName);

    resume();
}

namespace libj {
namespace trace {

void on() {
    if (!isEnabled) {
        assert(whiteList()->empty());
        assert(blackList()->empty());
        isEnabled = true;
    }
}

void off() {
    if (isEnabled) {
        isEnabled = false;
        clear();
    }
}

bool include(const char* pattern) {
    libj::glue::RegExp* re = createRegExp(pattern);
    if (re) {
        whiteList()->push_back(re);
        return true;
    } else {
        return false;
    }
}

bool exclude(const char* pattern) {
    libj::glue::RegExp* re = createRegExp(pattern);
    if (re) {
        blackList()->push_back(re);
        return true;
    } else {
        return false;
    }
}

}  // namespace trance
}  // namespace libj

#endif  // LIBJ_TRACE
