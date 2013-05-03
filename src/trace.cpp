// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/trace.h>
#include <libj/glue/regexp.h>

#include <assert.h>
#include <cxxabi.h>
#include <dlfcn.h>
#include <stdio.h>

#include <vector>

static bool isEnabled = false;
static bool wasEnabled = false;

static void resume() {
    isEnabled = wasEnabled;
}

static void stop() {
    wasEnabled = isEnabled;
    isEnabled = false;
}

static std::string convert(const char* s) {
    assert(libj::glue::RegExp::encoding() == libj::glue::RegExp::UTF16);
    std::basic_string<uint16_t> s16;
    for (size_t i = 0; s[i]; i++) {
        s16 += static_cast<uint16_t>(s[i]);
    }
    return std::string(
        reinterpret_cast<const char*>(s16.c_str()),
        s16.length() << 1);
}

static libj::glue::RegExp* createRegExp(const char* pattern) {
    if (!isEnabled || !pattern) {
        return NULL;
    } else {
        return libj::glue::RegExp::create(convert(pattern), 0);
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
    for (itr = whiteList()->begin(); itr != whiteList()->end(); itr++) {
        delete *itr;
    }
    whiteList()->clear();

    for (itr = blackList()->begin(); itr != blackList()->end(); itr++) {
        delete *itr;
    }
    blackList()->clear();
}

static bool isPrintable(const char* funcName) {
    if (!funcName) return false;

    std::string name = convert(funcName);
    std::vector<int> captures;
    std::vector<libj::glue::RegExp*>::const_iterator itr;

    for (itr = blackList()->begin(); itr != blackList()->end(); itr++) {
        if ((*itr)->execute(name, 0, captures)) {
            return false;
        }
    }

    for (itr = whiteList()->begin(); itr != whiteList()->end(); itr++) {
        if ((*itr)->execute(name, 0, captures)) {
            return true;
        }
    }

    return false;
}

static const char* addrToName(void* address) {
    Dl_info dli;
    if (dladdr(address, &dli)) {
        int status;
        return abi::__cxa_demangle(dli.dli_sname, 0, 0, &status);
    } else {
        return "<unknown>";
    }
}

extern "C" {
    void __cyg_profile_func_enter(void* funcAddress, void* callSite);
    void __cyg_profile_func_exit(void* funcAddress, void* callSite);
}

void __cyg_profile_func_enter(void* funcAddress, void* callSite) {
    if (!isEnabled || whiteList()->empty()) return;

    stop();

    const char* funcName = addrToName(funcAddress);
    if (isPrintable(funcName)) {
        printf("[LIBJ TRACE] enter: %s\n", funcName);
    }

    resume();
}

void __cyg_profile_func_exit(void* funcAddress, void* callSite) {
    if (!isEnabled || whiteList()->empty()) return;

    stop();

    const char* funcName = addrToName(funcAddress);
    if (isPrintable(funcName)) {
        printf("[LIBJ TRACE] exit:  %s\n", funcName);
    }

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
