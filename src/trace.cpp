// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/debug.h>
#include <libj/trace.h>

#include <cxxabi.h>
#include <dlfcn.h>

#include <set>
#include <string>

extern "C" {
    void __cyg_profile_func_enter(void* funcAddress, void* callSite);
    void __cyg_profile_func_exit(void* funcAddress, void* callSite);
}

static std::set<std::string>* includes() {
    static std::set<std::string> is;
    return &is;
}

static std::set<std::string>* excludes() {
    static std::set<std::string> es;
    return &es;
}

static bool isPrintable(const char* name) {
    if (!name) return false;

    for (std::set<std::string>::const_iterator itr = excludes()->begin();
         itr != excludes()->end();
         itr++) {
        size_t len = itr->length();
        if (!itr->compare(0, len, name, len)) {
            return false;
        }
    }

    for (std::set<std::string>::const_iterator itr = includes()->begin();
         itr != includes()->end();
         itr++) {
        size_t len = itr->length();
        if (!itr->compare(0, len, name, len)) {
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

void __cyg_profile_func_enter(void* funcAddress, void* callSite) {
    if (includes()->empty()) return;

    const char* funcName = addrToName(funcAddress);
    if (isPrintable(funcName)) {
        LIBJ_DEBUG_PRINT("enter: %s", funcName);
    }
}

void __cyg_profile_func_exit(void* funcAddress, void* callSite) {
    if (includes()->empty()) return;

    const char* funcName = addrToName(funcAddress);
    if (isPrintable(funcName)) {
        LIBJ_DEBUG_PRINT("exit:  %s", funcName);
    }
}

namespace libj {
namespace trace {

void include(const char* prefix) {
    includes()->insert(prefix);
}

void exclude(const char* prefix) {
    excludes()->insert(prefix);
}

}  // namespace trance
}  // namespace libj
