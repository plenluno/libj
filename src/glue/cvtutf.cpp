// Copyright (c) 2012 Plenluno All rights reserved.

#include <assert.h>
#include <errno.h>
#include <iconv.h>

// #define LIBJ_CVTUTF_DEBUG
#ifdef LIBJ_CVTUTF_DEBUG
    #include <stdio.h>
    #define ICONV iconvDebug
#else
    #define ICONV iconv
#endif  // LIBJ_CVTUTF_DEBUG

#include "./cvtutf.h"

namespace libj {
namespace glue {

static bool isBigEndian() {
    static union {
        uint32_t i;
        uint8_t c[4];
    } u = { 0x01020304 };

    return u.c[0] == 1;
}

static iconv_t iconvOpen(const char* inEnc, UnicodeEncoding outEnc) {
    iconv_t cd;
    switch (outEnc) {
    case UTF8:
        cd = iconv_open("UTF-8", inEnc);
        break;
    case UTF16BE:
        cd = iconv_open("UTF-16BE", inEnc);
        break;
    case UTF16LE:
        cd = iconv_open("UTF-16LE", inEnc);
        break;
    case UTF32BE:
        cd = iconv_open("UTF-32BE", inEnc);
        break;
    case UTF32LE:
        cd = iconv_open("UTF-32LE", inEnc);
        break;
    default:
        assert(false);
    }
    assert(cd != reinterpret_cast<iconv_t>(-1));
    return cd;
}

static iconv_t iconvOpen(UnicodeEncoding inEnc, const char* outEnc) {
    iconv_t cd;
    switch (inEnc) {
    case UTF8:
        cd = iconv_open(outEnc, "UTF-8");
        break;
    case UTF16BE:
        cd = iconv_open(outEnc, "UTF-16BE");
        break;
    case UTF16LE:
        cd = iconv_open(outEnc, "UTF-16LE");
        break;
    case UTF32BE:
        cd = iconv_open(outEnc, "UTF-32BE");
        break;
    case UTF32LE:
        cd = iconv_open(outEnc, "UTF-32LE");
        break;
    default:
        assert(false);
    }
    assert(cd != reinterpret_cast<iconv_t>(-1));
    return cd;
}

static iconv_t iconvOpenFromUtf32(UnicodeEncoding outEnc) {
    const char* inEnc;
    if (isBigEndian()) {
        inEnc = "UTF-32BE";
    } else {
        inEnc = "UTF-32LE";
    }
    return iconvOpen(inEnc, outEnc);
}

static iconv_t iconvOpenToUtf32(UnicodeEncoding inEnc) {
    const char* outEnc;
    if (isBigEndian()) {
        outEnc = "UTF-32BE";
    } else {
        outEnc = "UTF-32LE";
    }
    return iconvOpen(inEnc, outEnc);
}

static void iconClose(iconv_t cd) {
    iconv_close(cd);
}

#ifdef LIBJ_CVTUTF_DEBUG
static size_t iconvDebug(
    iconv_t cd,
    char **inBuf, size_t *inBytesLeft,
    char **outBuf, size_t *outBytesLeft) {
    char* inStart = *inBuf;
    char* outStart = *outBuf;
    size_t inBytes = *inBytesLeft;
    size_t outBytes = *outBytesLeft;

    size_t ret = iconv(cd, inBuf, inBytesLeft, outBuf, outBytesLeft);

    printf("return: %zd\n", ret);
    if (ret) {
        switch(errno) {
        case EILSEQ:
            printf("errno: EILSEQ\n");
            break;
        case EINVAL:
            printf("errno: EINVAL\n");
            break;
        case E2BIG:
            printf("errno: E2BIG\n");
            break;
        default:
            assert(false);
        }
    }

    printf("inbytesleft: %zd -> %zd\n", inBytes, *inBytesLeft);
    printf("outbytesleft: %zd -> %zd\n", outBytes, *outBytesLeft);
    assert(*inBuf - inStart == inBytes - *inBytesLeft);
    assert(*outBuf - outStart == outBytes - *outBytesLeft);

    return ret;
}
#endif  // LIBJ_CVTUTF_DEBUG

std::string fromUtf32(const std::u32string& str, UnicodeEncoding enc) {
    std::string s;
    iconv_t cd = iconvOpenFromUtf32(enc);
    char* inBuf = reinterpret_cast<char*>(const_cast<char32_t*>(str.c_str()));
    size_t inLen = str.length();
    for (size_t i = 0; i < inLen; i++) {
#ifdef LIBJ_CVTUTF_DEBUG
        printf("fromUtf32[%zd]: %d\n", i, str[i]);
#endif  // LIBJ_CVTUTF_DEBUG
        size_t inBytesLeft = 4;
        char c8[8];
        char* outBuf = c8;
        size_t outBytesLeft = 8;
        size_t ret = ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        assert(outBytesLeft < 8);
        size_t outLen = 8 - outBytesLeft;
        for (size_t j = 0; j < outLen; j++) {
            s += c8[j];
        }
    }
    if (enc == UTF16BE || enc == UTF16LE) {
        for (int i = 0; i < 2; i++) {
            s += static_cast<char>(0);
        }
    } else if (enc == UTF32BE || enc == UTF32LE) {
        for (int i = 0; i < 4; i++) {
            s += static_cast<char>(0);
        }
    }
    iconClose(cd);
    return s;
}

std::u32string toUtf32(const void* data, UnicodeEncoding enc, size_t max) {
    if (!data) return std::u32string();

    std::u32string s32;
    iconv_t cd = iconvOpenToUtf32(enc);
    char* inBuf = static_cast<char*>(const_cast<void*>(data));
    for (size_t i = 0; i < max; i++) {
        size_t inBytesLeft = 8;
        union {
            char32_t c32;
            char c8[4];
        } u;
        char* outBuf = u.c8;
        size_t outBytesLeft = 4;
        size_t ret = ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        if (outBytesLeft || !u.c32) {
            break;
        } else {
#ifdef LIBJ_CVTUTF_DEBUG
        printf("toUtf32[%zd]: %d\n", i, u.c32);
#endif  // LIBJ_CVTUTF_DEBUG
            s32 += u.c32;
        }
    }
    iconClose(cd);
    return s32;
}

std::u32string utf16ToUtf32(const std::u16string& str) {
    if (isBigEndian()) {
        return toUtf32(str.c_str(), UTF16BE, -1);
    } else {
        return toUtf32(str.c_str(), UTF16LE, -1);
    }
}

std::u16string utf32ToUtf16(const std::u32string& str) {
    std::u16string s;
    iconv_t cd;
    if (isBigEndian()) {
        cd = iconvOpenFromUtf32(UTF16BE);
    } else {
        cd = iconvOpenFromUtf32(UTF16LE);
    }
    char* inBuf = reinterpret_cast<char*>(const_cast<char32_t*>(str.c_str()));
    size_t inLen = str.length();
    for (size_t i = 0; i < inLen; i++) {
        size_t inBytesLeft = 4;
        union {
            char16_t c16[4];
            char c8[8];
        } u;
        char* outBuf = u.c8;
        size_t outBytesLeft = 8;
        size_t ret = ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        assert(outBytesLeft < 8);
        size_t outLen = (8 - outBytesLeft) >> 1;
        for (size_t j = 0; j < outLen; j++) {
            s += u.c16[j];
        }
    }
    iconClose(cd);
    return s;
}

}  // namespace glue
}  // namespace libj
