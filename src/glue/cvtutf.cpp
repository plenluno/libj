// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/config.h>
#include <libj/endian.h>
#include <libj/glue/cvtutf.h>

#include <assert.h>

#ifdef LIBJ_USE_ICONV
    #include <errno.h>
    #include <iconv.h>
#else
    #include <ConvertUTF.h>
#endif

namespace libj {
namespace glue {

static inline bool isBigEndian() {
    static bool big = endian() == BIG;
    return big;
}

static inline bool needsSwap(UnicodeEncoding enc) {
    switch (enc) {
    case UTF16BE:
        return !isBigEndian();
    case UTF16LE:
        return isBigEndian();
    case UTF32BE:
        return !isBigEndian();
    case UTF32LE:
        return isBigEndian();
    default:
        return false;
    }
}

static inline char16_t swapChar16(char16_t c16) {
    uint16_t u16 = static_cast<uint16_t>(c16);
    return (u16 << 8) | (u16 >> 8);
}

static inline char32_t swapChar32(char32_t c32) {
    uint32_t u32 = static_cast<uint32_t>(c32);
    u32 = ((u32 << 8) & 0xFF00FF00) | ((u32 >> 8) & 0xFF00FF);
    return (u32 << 16) | (u32 >> 16);
}

size_t byteLengthAt(const void* data, UnicodeEncoding enc) {
    switch (enc) {
    case UTF8: {
            uint8_t c = static_cast<const uint8_t*>(data)[0];
            if (c < 0x80) {
                return 1;
            } else if (c < 0xe0) {
                return 2;
            } else if (c < 0xf0) {
                return 3;
            } else if (c < 0xf8) {
                return 4;
            } else if (c < 0xfc) {
                return 5;
            } else if (c < 0xfe) {
                return 6;
            } else {
                return 0;
            }
        }
    case UTF16BE: {
            uint16_t c = static_cast<const uint16_t*>(data)[0];
            if ((c & 0x00f8) == 0x00d8) {
                return 4;
            } else {
                return 2;
            }
        }
    case UTF16LE: {
            uint16_t c = static_cast<const uint16_t*>(data)[0];
            if ((c & 0xf800) == 0xd800) {
                return 4;
            } else {
                return 2;
            }
        }
    case UTF32BE:
    case UTF32LE:
        return 4;
    default:
        assert(false);
        return 0;
    }
}

std::string utf16ToUtf8(const std::u16string& str, size_t* n) {
    assert(sizeof(char16_t) == 2);

    if (isBigEndian()) {
        return toUtf8(str.c_str(), UTF16BE, -1, n);
    } else {
        return toUtf8(str.c_str(), UTF16LE, -1, n);
    }
}

std::u32string utf16ToUtf32(const std::u16string& str) {
    assert(sizeof(char16_t) == 2);

    if (isBigEndian()) {
        return toUtf32(str.c_str(), UTF16BE, -1);
    } else {
        return toUtf32(str.c_str(), UTF16LE, -1);
    }
}

#ifdef LIBJ_USE_ICONV

#ifdef LIBJ_CVTUTF_DEBUG
    #include <stdio.h>
    #define ICONV iconvDebug
#else
    #define ICONV iconv
#endif

static inline iconv_t iconvOpen(const char* inEnc, UnicodeEncoding outEnc) {
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

static inline iconv_t iconvOpen(UnicodeEncoding inEnc, const char* outEnc) {
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

static inline iconv_t iconvOpenFromUtf16(UnicodeEncoding outEnc) {
    const char* inEnc;
    if (isBigEndian()) {
        inEnc = "UTF-16BE";
    } else {
        inEnc = "UTF-16LE";
    }
    return iconvOpen(inEnc, outEnc);
}

static inline iconv_t iconvOpenFromUtf32(UnicodeEncoding outEnc) {
    const char* inEnc;
    if (isBigEndian()) {
        inEnc = "UTF-32BE";
    } else {
        inEnc = "UTF-32LE";
    }
    return iconvOpen(inEnc, outEnc);
}

static inline iconv_t iconvOpenToUtf16(UnicodeEncoding inEnc) {
    const char* outEnc;
    if (isBigEndian()) {
        outEnc = "UTF-16BE";
    } else {
        outEnc = "UTF-16LE";
    }
    return iconvOpen(inEnc, outEnc);
}

static inline iconv_t iconvOpenToUtf32(UnicodeEncoding inEnc) {
    const char* outEnc;
    if (isBigEndian()) {
        outEnc = "UTF-32BE";
    } else {
        outEnc = "UTF-32LE";
    }
    return iconvOpen(inEnc, outEnc);
}

static inline void iconvClose(iconv_t cd) {
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
        switch (errno) {
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

    printf("inBytesLeft: %zd -> %zd\n", inBytes, *inBytesLeft);
    printf("outBytesLeft: %zd -> %zd\n", outBytes, *outBytesLeft);
    assert(*inBuf - inStart == inBytes - *inBytesLeft);
    assert(*outBuf - outStart == outBytes - *outBytesLeft);

    return ret;
}
#endif  // LIBJ_CVTUTF_DEBUG

char32_t codePointAt(const void* data, UnicodeEncoding enc) {
    iconv_t cd = iconvOpenToUtf32(enc);
    char* inBuf = static_cast<char*>(const_cast<void*>(data));
    size_t inBytesLeft = byteLengthAt(inBuf, enc);
    if (!inBytesLeft) return -1;

    union {
        char32_t c32;
        char c8[4];
    } u;
    char* outBuf = u.c8;
    size_t outBytesLeft = 4;
    ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
    assert(!outBytesLeft);
    iconvClose(cd);
    return u.c32;
}

std::string fromUtf8(const std::string& str, UnicodeEncoding enc) {
    assert(sizeof(char) == 1);

    std::string s;
    iconv_t cd = iconvOpen("UTF-8", enc);
    char* inBuf = const_cast<char*>(str.c_str());
    size_t inLen = str.length();
    for (size_t i = 0; i < inLen;) {
        size_t byteLen = byteLengthAt(inBuf, UTF8);
        assert(byteLen);
        size_t inBytesLeft = byteLen;
        char c8[8];
        char* outBuf = c8;
        size_t outBytesLeft = 8;
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        assert(inBytesLeft == 0 && outBytesLeft < 8);
        size_t outLen = 8 - outBytesLeft;
        for (size_t j = 0; j < outLen; j++) {
            s += c8[j];
        }
        i += byteLen;
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
    iconvClose(cd);
    return s;
}

std::string fromUtf16(const std::u16string& str, UnicodeEncoding enc) {
    assert(sizeof(char) == 1 && sizeof(char16_t) == 2);

    std::string s;
    iconv_t cd = iconvOpenFromUtf16(enc);
    char* inBuf = reinterpret_cast<char*>(const_cast<char16_t*>(str.c_str()));
    size_t inLen = str.length();
    for (size_t i = 0; i < inLen;) {
        size_t byteLen;
        if (isBigEndian()) {
            byteLen = byteLengthAt(inBuf, UTF16BE);
        } else {
            byteLen = byteLengthAt(inBuf, UTF16LE);
        }
        assert(byteLen);
        size_t inBytesLeft = byteLen;
        char c8[8];
        char* outBuf = c8;
        size_t outBytesLeft = 8;
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        assert(outBytesLeft < 8);
        size_t outLen = 8 - outBytesLeft;
        for (size_t j = 0; j < outLen; j++) {
            s += c8[j];
        }
        i += byteLen >> 1;
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
    iconvClose(cd);
    return s;
}

std::string fromUtf32(const std::u32string& str, UnicodeEncoding enc) {
    assert(sizeof(char) == 1 && sizeof(char32_t) == 4);

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
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
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
    iconvClose(cd);
    return s;
}

std::string toUtf8(
    const void* data, UnicodeEncoding enc, size_t max, size_t* n) {
    assert(sizeof(char) == 1);

    if (!data) return std::string();

    std::string s8;
    iconv_t cd = iconvOpen(enc, "UTF-8");
    char* inBuf = static_cast<char*>(const_cast<void*>(data));
    size_t i = 0;
    for (; i < max; i++) {
        size_t byteLen = byteLengthAt(inBuf, enc);
        size_t inBytesLeft = byteLen;
        if (!inBytesLeft) break;

        char buf[7];
        char* outBuf = buf;
        size_t outBytesLeft = 7;
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        assert(!inBytesLeft && outBytesLeft < 7);
        if (outBytesLeft == 6 && !buf[0]) {
            break;
        } else {
            buf[7 - outBytesLeft] = 0;
            s8 += buf;
        }
#ifdef LIBJ_CVTUTF_DEBUG
        printf("toUtf8[%zd]: %ld %s\n", i, byteLen, buf);
#endif  // LIBJ_CVTUTF_DEBUG
    }
    iconvClose(cd);

    if (n) *n = i;
    return s8;
}

std::u16string toUtf16(const void* data, UnicodeEncoding enc, size_t max) {
    assert(sizeof(char) == 1 && sizeof(char16_t) == 2);

    if (!data) return std::u16string();

    std::u16string s16;
    iconv_t cd = iconvOpenToUtf16(enc);
    char* inBuf = static_cast<char*>(const_cast<void*>(data));
    for (size_t i = 0; i < max; i++) {
        size_t inBytesLeft = byteLengthAt(inBuf, enc);
        if (!inBytesLeft) break;

        union {
            char16_t c16[2];
            char c8[4];
        } u;
        char* outBuf = u.c8;
        size_t outBytesLeft = 4;
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        if (outBytesLeft == 4) {
            break;
        } else if (outBytesLeft == 2) {
            if (u.c16[0]) {
                s16 += u.c16[0];
            } else {
                break;
            }
        } else {
            s16 += u.c16[0];
            s16 += u.c16[1];
        }
    }
    iconvClose(cd);
    return s16;
}

std::u32string toUtf32(const void* data, UnicodeEncoding enc, size_t max) {
    assert(sizeof(char) == 1 && sizeof(char32_t) == 4);

    if (!data) return std::u32string();

    std::u32string s32;
    iconv_t cd = iconvOpenToUtf32(enc);
    char* inBuf = static_cast<char*>(const_cast<void*>(data));
    for (size_t i = 0; i < max; i++) {
        size_t inBytesLeft = byteLengthAt(inBuf, enc);
        if (!inBytesLeft) break;

        union {
            char32_t c32;
            char c8[4];
        } u;
        char* outBuf = u.c8;
        size_t outBytesLeft = 4;
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        if (outBytesLeft || !u.c32) {
            break;
        } else {
#ifdef LIBJ_CVTUTF_DEBUG
        printf("toUtf32[%zd]: %d\n", i, u.c32);
#endif  // LIBJ_CVTUTF_DEBUG
            s32 += u.c32;
        }
    }
    iconvClose(cd);
    return s32;
}

std::u16string utf8ToUtf16(const std::string& str, size_t* n) {
    assert(sizeof(char) == 1 && sizeof(char16_t) == 2);

    std::u16string s;
    iconv_t cd;
    if (isBigEndian()) {
        cd = iconvOpen("UTF-8", UTF16BE);
    } else {
        cd = iconvOpen("UTF-8", UTF16LE);
    }
    char* inBuf = const_cast<char*>(str.c_str());
    size_t inLen = str.length();
    size_t num = 0;
    for (size_t i = 0; i < inLen;) {
        size_t byteLen = byteLengthAt(inBuf, UTF8);
        size_t inBytesLeft = byteLen;
        union {
            char16_t c16[2];
            char c8[4];
        } u;
        char* outBuf = u.c8;
        size_t outBytesLeft = 4;
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        assert(outBytesLeft < 4);
        size_t outLen = (4 - outBytesLeft) >> 1;
        for (size_t j = 0; j < outLen; j++) {
            s += u.c16[j];
        }
        i += byteLen;
        num++;
    }
    iconvClose(cd);

    if (n) *n = num;
    return s;
}

std::u16string utf32ToUtf16(const std::u32string& str) {
    assert(sizeof(char) == 1 && sizeof(char16_t) == 2 && sizeof(char32_t) == 4);

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
        ICONV(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
        assert(outBytesLeft < 8);
        size_t outLen = (8 - outBytesLeft) >> 1;
        for (size_t j = 0; j < outLen; j++) {
            s += u.c16[j];
        }
    }
    iconvClose(cd);
    return s;
}

#else  // LIBJ_USE_ICONV

static size_t findUtf8End(
    const unsigned char* start,
    size_t max,
    const unsigned char** end) {
    size_t n = 0;
    const unsigned char* pos = start;
    for (; n < max; n++) {
        unsigned char c = *pos;
        if (c) {
            pos += getNumBytesForUTF8(c);
        } else {
            break;
        }
    }
    *end = pos;
    return n;
}

static size_t findUtf16End(
    const char16_t* start,
    UnicodeEncoding enc,
    size_t max,
    const char16_t** end,
    std::u16string** swaped) {
    if (!max) {
        *end = start;
        *swaped = NULL;
        return 0;
    }

    bool swap = needsSwap(enc);
    if (swap) {
        *swaped = new std::u16string();
    } else {
        *swaped = NULL;
    }

    size_t n = 0;
    const char16_t* pos = start;
    for (; n < max; n++) {
        char16_t c16 = *pos;
        if (c16) {
            if (swap) {
                c16 = swapChar16(c16);
                **swaped += c16;
            }
            pos++;

            if (isSurrogatePair(c16)) {
                if (swap) {
                    **swaped += swapChar16(*pos);
                }
                pos++;
            }
        } else {
            break;
        }
    }
    *end = pos;
    return n;
}

static size_t findUtf32End(
    const char32_t* start,
    UnicodeEncoding enc,
    size_t max,
    const char32_t** end,
    std::u32string** swaped) {
    if (!max) {
        *end = start;
        *swaped = NULL;
        return 0;
    }

    bool swap = needsSwap(enc);
    if (swap) {
        *swaped = new std::u32string();
    } else {
        *swaped = NULL;
    }

    size_t n = 0;
    const char32_t* pos = start;
    for (; n < max; n++) {
        char32_t c32 = *pos;
        if (c32) {
            if (swap) {
                c32 = swapChar32(c32);
                **swaped += c32;
            }
            pos++;
        } else {
            break;
        }
    }
    *end = pos;
    return n;
}

static std::string utf8ToUtf8(
    const unsigned char* data,
    size_t max,
    size_t* n = NULL) {
    assert(data && sizeof(unsigned char) == 1);

    const unsigned char* end;
    size_t num = findUtf8End(data, max, &end);
    if (n) *n = num;
    if (!num) return std::string();

    return std::string(reinterpret_cast<const char*>(data), end - data);
}

static std::u16string utf8ToUtf16(
    const unsigned char* data,
    size_t max,
    size_t* n = NULL) {
    assert(data && sizeof(unsigned char) == 1 && sizeof(char16_t) == 2);

    const unsigned char* end;
    size_t num = findUtf8End(data, max, &end);
    if (n) *n = num;
    if (!num) return std::u16string();

    const unsigned char* sourceStart = data;
    const unsigned char* sourceEnd = end;

    num <<= 1;
    char16_t* out = new char16_t[num];
    char16_t* targetStart = out;
    char16_t* targetEnd = out + num;

    ConvertUTF8toUTF16(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    num = targetStart - out;
#ifdef LIBJ_USE_UTF16
    num = num < max ? num : max;
#endif
    std::u16string u16s(out, num);
    delete[] out;
    return u16s;
}

static std::u32string utf8ToUtf32(
    const unsigned char* data,
    size_t max) {
    assert(data && sizeof(unsigned char) == 1 && sizeof(char32_t) == 4);

    const unsigned char* end;
    size_t n = findUtf8End(data, max, &end);
    if (!n) return std::u32string();

    const unsigned char* sourceStart = data;
    const unsigned char* sourceEnd = end;

    char32_t* out = new char32_t[n];
    char32_t* targetStart = out;
    char32_t* targetEnd = out + n;

    ConvertUTF8toUTF32(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    std::u32string u32s(out, targetStart - out);
    delete[] out;
    return u32s;
}

static std::string utf16ToUtf8(
    const char16_t* data,
    UnicodeEncoding enc,
    size_t max,
    size_t* n = NULL) {
    assert(data && sizeof(unsigned char) == 1 && sizeof(char16_t) == 2);

    const char16_t* end;
    std::u16string* u16s;
    size_t num = findUtf16End(data, enc, max, &end, &u16s);
    if (n) *n = num;
    if (!num) {
        delete u16s;
        return std::string();
    }

    const char16_t* sourceStart;
    const char16_t* sourceEnd;
    if (u16s) {
        sourceStart = u16s->c_str();
        sourceEnd = sourceStart + u16s->length();
    } else {
        sourceStart = data;
        sourceEnd = end;
    }

    num *= 6;
    unsigned char* out = new unsigned char[num];
    unsigned char* targetStart = out;
    unsigned char* targetEnd = out + num;

    ConvertUTF16toUTF8(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    std::string u8s(reinterpret_cast<const char*>(out), targetStart - out);
    delete u16s;
    delete[] out;
    return u8s;
}

static std::u16string utf16ToUtf16(
    const char16_t* data,
    UnicodeEncoding enc,
    size_t max) {
    assert(data);

    if (!max) return std::u16string();

    std::u16string u16s;
    size_t n = 0;
    const char16_t* pos = data;
    bool swap = needsSwap(enc);
    for (; n < max; n++, pos++) {
        char16_t c16 = *pos;
        if (c16) {
            if (swap) c16 = swapChar16(c16);
            u16s += c16;
        } else {
            break;
        }
    }
    return u16s;
}

static std::u32string utf16ToUtf32(
    const char16_t* data,
    UnicodeEncoding enc,
    size_t max) {
    assert(data && sizeof(char16_t) == 2 && sizeof(char32_t) == 4);

    const char16_t* end;
    std::u16string* u16s;
    size_t n = findUtf16End(data, enc, max, &end, &u16s);
    if (!n) {
        delete u16s;
        return std::u32string();
    }

    const char16_t* sourceStart;
    const char16_t* sourceEnd;
    if (u16s) {
        sourceStart = u16s->c_str();
        sourceEnd = sourceStart + u16s->length();
    } else {
        sourceStart = data;
        sourceEnd = end;
    }

    char32_t* out = new char32_t[n];
    char32_t* targetStart = out;
    char32_t* targetEnd = out + n;

    ConvertUTF16toUTF32(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    std::u32string u32s(out, targetStart - out);
    delete u16s;
    delete[] out;
    return u32s;
}

static std::string utf32ToUtf8(
    const char32_t* data,
    UnicodeEncoding enc,
    size_t max,
    size_t* n = NULL) {
    assert(data && sizeof(unsigned char) == 1 && sizeof(char32_t) == 4);

    const char32_t* end;
    std::u32string* u32s;
    size_t num = findUtf32End(data, enc, max, &end, &u32s);
    if (n) *n = num;
    if (!num) {
        delete u32s;
        return std::string();
    }

    const char32_t* sourceStart;
    const char32_t* sourceEnd;
    if (u32s) {
        sourceStart = u32s->c_str();
        sourceEnd = sourceStart + u32s->length();
    } else {
        sourceStart = data;
        sourceEnd = end;
    }

    num *= 6;
    unsigned char* out = new unsigned char[num];
    unsigned char* targetStart = out;
    unsigned char* targetEnd = out + num;

    ConvertUTF32toUTF8(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    std::string u8s(reinterpret_cast<const char*>(out), targetStart - out);
    delete u32s;
    delete[] out;
    return u8s;
}

static std::u16string utf32ToUtf16(
    const char32_t* data,
    UnicodeEncoding enc,
    size_t max,
    size_t* n = NULL) {
    assert(data && sizeof(char16_t) == 2 && sizeof(char32_t) == 4);

    const char32_t* end;
    std::u32string* u32s;
    size_t num = findUtf32End(data, enc, max, &end, &u32s);
    if (n) *n = num;
    if (!num) {
        delete u32s;
        return std::u16string();
    }

    const char32_t* sourceStart;
    const char32_t* sourceEnd;
    if (u32s) {
        sourceStart = u32s->c_str();
        sourceEnd = sourceStart + u32s->length();
    } else {
        sourceStart = data;
        sourceEnd = end;
    }

    num *= 2;
    char16_t* out = new char16_t[num];
    char16_t* targetStart = out;
    char16_t* targetEnd = out + num;

    ConvertUTF32toUTF16(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    num = targetStart - out;
#ifdef LIBJ_USE_UTF16
    num = num < max ? num : max;
#endif
    std::u16string u16s(reinterpret_cast<const char16_t*>(out), num);
    delete u32s;
    delete[] out;
    return u16s;
}

static std::u32string utf32ToUtf32(
    const char32_t* data,
    UnicodeEncoding enc,
    size_t max) {
    assert(data);

    if (!max) return std::u32string();

    std::u32string u32s;
    size_t n = 0;
    const char32_t* pos = data;
    bool swap = needsSwap(enc);
    for (; n < max; n++, pos++) {
        char32_t c32 = *pos;
        if (c32) {
            if (swap) c32 = swapChar32(c32);
            if (c32 <= UNI_MAX_LEGAL_UTF32) {
                u32s += c32;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    return u32s;
}

std::u16string utf8ToUtf16(const std::string& str, size_t* n) {
    if (isBigEndian()) {
        return utf8ToUtf16(
            reinterpret_cast<const unsigned char*>(str.c_str()), -1, n);
    } else {
        return utf8ToUtf16(
            reinterpret_cast<const unsigned char*>(str.c_str()), -1, n);
    }
}

static std::string utf32ToUtf8(const std::u32string& str) {
    if (isBigEndian()) {
        return utf32ToUtf8(str.c_str(), UTF32BE, -1);
    } else {
        return utf32ToUtf8(str.c_str(), UTF32LE, -1);
    }
}

std::u16string utf32ToUtf16(const std::u32string& str) {
    if (isBigEndian()) {
        return utf32ToUtf16(str.c_str(), UTF32BE, -1);
    } else {
        return utf32ToUtf16(str.c_str(), UTF32LE, -1);
    }
}

static std::string toStdString(
    const std::u16string& str,
    UnicodeEncoding enc) {
    std::u16string u16s;
    bool swap = needsSwap(enc);
    size_t len = str.length();
    for (size_t i = 0; i < len; i++) {
        char16_t c16 = str[i];
        if (c16) {
            if (swap) c16 = swapChar16(c16);
            u16s += c16;
        } else {
            break;
        }
    }
    u16s += static_cast<char16_t>(0);
    return std::string(
        reinterpret_cast<const char*>(u16s.c_str()),
        u16s.length() << 1);
}

static std::string toStdString(
    const std::u32string& str,
    UnicodeEncoding enc) {
    std::u32string u32s;
    bool swap = needsSwap(enc);
    size_t len = str.length();
    for (size_t i = 0; i < len; i++) {
        char32_t c32 = str[i];
        if (c32 > 0 && c32 <= UNI_MAX_LEGAL_UTF32) {
            if (swap) c32 = swapChar32(c32);
            u32s += c32;
        } else {
            break;
        }
    }
    u32s += static_cast<char32_t>(0);
    return std::string(
        reinterpret_cast<const char*>(u32s.c_str()),
        u32s.length() << 2);
}

static char32_t toCodePoint(const unsigned char* data) {
    assert(data && sizeof(unsigned char) == 1);

    const unsigned char* sourceStart = data;
    const unsigned char* sourceEnd = data + byteLengthAt(data, UTF8);

    char32_t codePoint;
    char32_t* targetStart = &codePoint;
    char32_t* targetEnd = &codePoint + 1;

    ConvertUTF8toUTF32(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    return (targetStart == &codePoint) ? 0 : codePoint;
}

static char32_t toCodePoint(const char16_t* data, UnicodeEncoding enc) {
    assert(data && sizeof(char16_t) == 2);

    size_t byteLen = byteLengthAt(data, enc);
    const char16_t* sourceStart;
    const char16_t* sourceEnd;

    char16_t u16s[2];
    if (needsSwap(enc)) {
        u16s[0] = swapChar16(data[0]);
        if (byteLen == 4) {
            u16s[1] = swapChar16(data[1]);
        }
        sourceStart = u16s;
        sourceEnd = u16s + (byteLen >> 1);
    } else {
        sourceStart = data;
        sourceEnd = data + (byteLen >> 1);
    }

    char32_t codePoint;
    char32_t* targetStart = &codePoint;
    char32_t* targetEnd = &codePoint + 1;

    ConvertUTF16toUTF32(
        &sourceStart,
        sourceEnd,
        &targetStart,
        targetEnd,
        strictConversion);

    return (targetStart == &codePoint) ? 0 : codePoint;
}

static char32_t toCodePoint(const char32_t* data, UnicodeEncoding enc) {
    assert(data && sizeof(char32_t) == 4);

    if (needsSwap(enc)) {
        return swapChar32(*data);
    } else {
        return *data;
    }
}

char32_t codePointAt(const void* data, UnicodeEncoding enc) {
    switch (enc) {
    case UTF8:
        return toCodePoint(static_cast<const unsigned char*>(data));
    case UTF16BE:
    case UTF16LE:
        return toCodePoint(static_cast<const char16_t*>(data), enc);
    case UTF32BE:
    case UTF32LE:
        return toCodePoint(static_cast<const char32_t*>(data), enc);
    }
}

std::string fromUtf8(const std::string& str, UnicodeEncoding enc) {
    const unsigned char* cstr =
        reinterpret_cast<const unsigned char*>(str.c_str());
    switch (enc) {
    case UTF8:
        return str;
    case UTF16BE:
    case UTF16LE:
        return toStdString(utf8ToUtf16(cstr, -1), enc);
    case UTF32BE:
    case UTF32LE:
        return toStdString(utf8ToUtf32(cstr, -1), enc);
    }
}

std::string fromUtf16(const std::u16string& str, UnicodeEncoding enc) {
    const unsigned char* cstr =
        reinterpret_cast<const unsigned char*>(str.c_str());
    switch (enc) {
    case UTF8:
        return utf16ToUtf8(str);
    case UTF16BE:
    case UTF16LE:
        return toStdString(str, enc);
    case UTF32BE:
    case UTF32LE:
        return toStdString(utf16ToUtf32(str), enc);
    }
}

std::string fromUtf32(const std::u32string& str, UnicodeEncoding enc) {
    switch (enc) {
    case UTF8:
        return utf32ToUtf8(str);
    case UTF16BE:
    case UTF16LE:
        return toStdString(utf32ToUtf16(str), enc);
    case UTF32BE:
    case UTF32LE:
        return toStdString(str, enc);
    }
}

std::string toUtf8(
    const void* data, UnicodeEncoding enc, size_t max, size_t* n) {
    switch (enc) {
    case UTF8:
        return utf8ToUtf8(static_cast<const unsigned char*>(data), max, n);
    case UTF16BE:
    case UTF16LE:
        return utf16ToUtf8(static_cast<const char16_t*>(data), enc, max, n);
    case UTF32BE:
    case UTF32LE:
        return utf32ToUtf8(static_cast<const char32_t*>(data), enc, max, n);
    }
}

std::u16string toUtf16(
    const void* data, UnicodeEncoding enc, size_t max) {
    switch (enc) {
    case UTF8:
        return utf8ToUtf16(static_cast<const unsigned char*>(data), max);
    case UTF16BE:
    case UTF16LE:
        return utf16ToUtf16(static_cast<const char16_t*>(data), enc, max);
    case UTF32BE:
    case UTF32LE:
        return utf32ToUtf16(static_cast<const char32_t*>(data), enc, max);
    }
}

std::u32string toUtf32(const void* data, UnicodeEncoding enc, size_t max) {
    switch (enc) {
    case UTF8:
        return utf8ToUtf32(static_cast<const unsigned char*>(data), max);
    case UTF16BE:
    case UTF16LE:
        return utf16ToUtf32(static_cast<const char16_t*>(data), enc, max);
    case UTF32BE:
    case UTF32LE:
        return utf32ToUtf32(static_cast<const char32_t*>(data), enc, max);
    }
}

#endif  // LIBJ_USE_ICONV

}  // namespace glue
}  // namespace libj
