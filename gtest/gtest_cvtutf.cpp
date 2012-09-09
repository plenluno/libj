// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <string>

#include "../src/glue/cvtutf.h"

namespace libj {
namespace glue {

TEST(GTestCvtUtf, TestUtf8ToUtf32) {
    std::u32string s32;
    char s1[] = { 0xe3, 0x81, 0x82, 0x00 };
    s32 = toUtf32(s1, UTF8, 0);
    ASSERT_EQ(0, s32.length());
    s32 = toUtf32(s1, UTF8, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);
    s32 = toUtf32(s1, UTF8, -1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);

    char s2[] = { 0xe3, 0x81, 0x82 };
    s32 = toUtf32(s2, UTF8, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);

    char s3[] = { 0xe3, 0x81, 0x00 };
    s32 = toUtf32(s3, UTF8, 1);
    ASSERT_EQ(0, s32.length());
}

TEST(GTestCvtUtf, TestUtf16BEToUtf32) {
    std::u32string s32;
    char s1[] = { 0x30, 0x42, 0x00, 0x00 };
    s32 = toUtf32(s1, UTF16BE, 0);
    ASSERT_EQ(0, s32.length());
    s32 = toUtf32(s1, UTF16BE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);
    s32 = toUtf32(s1, UTF16BE, -1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);

    char s2[] = { 0x30, 0x42 };
    s32 = toUtf32(s2, UTF16BE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);

    char s3[] = { 0xd8, 0x40, 0xdc, 0x0b };
    s32 = toUtf32(s3, UTF16BE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);

    char s4[] = { 0xdf, 0xff, 0xdf, 0xff };
    s32 = toUtf32(s4, UTF16BE, 1);
    ASSERT_EQ(0, s32.length());
}

TEST(GTestCvtUtf, TestUtf16LEToUtf32) {
    std::u32string s32;
    char s1[] = { 0x42, 0x30, 0x00, 0x00 };
    s32 = toUtf32(s1, UTF16LE, 0);
    ASSERT_EQ(0, s32.length());
    s32 = toUtf32(s1, UTF16LE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);
    s32 = toUtf32(s1, UTF16LE, -1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);

    char s2[] = { 0x42, 0x30 };
    s32 = toUtf32(s2, UTF16LE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x3042, s32[0]);

    char s3[] = { 0x40, 0xd8, 0x0b, 0xdc };
    s32 = toUtf32(s3, UTF16LE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);

    char s4[] = { 0xff, 0xdf, 0xff, 0xdf };
    s32 = toUtf32(s4, UTF16LE, 1);
    ASSERT_EQ(0, s32.length());
}

TEST(GTestCvtUtf, TestUtf32BEToUtf32) {
    std::u32string s32;
    char s1[] = {
        0x00, 0x02, 0x00, 0x0b,
        0x00, 0x00, 0x00, 0x00
    };
    s32 = toUtf32(s1, UTF32BE, 0);
    ASSERT_EQ(0, s32.length());
    s32 = toUtf32(s1, UTF32BE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);
    s32 = toUtf32(s1, UTF32BE, -1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);

    char s2[] = {
        0x00, 0x02, 0x00, 0x0b
    };
    s32 = toUtf32(s2, UTF32BE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);

    char s3[] = { 0xff, 0xff, 0xff, 0xff };
    s32 = toUtf32(s3, UTF32BE, 1);
    ASSERT_EQ(0, s32.length());
}

TEST(GTestCvtUtf, TestUtf32LEToUtf32) {
    std::u32string s32;
    char s1[] = {
        0x0b, 0x00, 0x02, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    s32 = toUtf32(s1, UTF32LE, 0);
    ASSERT_EQ(0, s32.length());
    s32 = toUtf32(s1, UTF32LE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);
    s32 = toUtf32(s1, UTF32LE, -1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);

    char s2[] = {
        0x0b, 0x00, 0x02, 0x00
    };
    s32 = toUtf32(s2, UTF32LE, 1);
    ASSERT_EQ(1, s32.length());
    ASSERT_EQ(0x2000b, s32[0]);

    char s3[] = { 0xff, 0xff, 0xff, 0xff };
    s32 = toUtf32(s3, UTF32LE, 1);
    ASSERT_EQ(0, s32.length());
}

TEST(GTestCvtUtf, TestUtf32ToUtf8) {
    std::u32string s32;
    std::string s8 = fromUtf32(s32, UTF8);
    ASSERT_EQ(0, s8.length());

    s32 += 0x3042;
    s32 += 0x3044;
    s8 = fromUtf32(s32, UTF8);
    ASSERT_EQ(6, s8.length());
    ASSERT_EQ(static_cast<char>(0xe3), s8[0]);
    ASSERT_EQ(static_cast<char>(0x81), s8[1]);
    ASSERT_EQ(static_cast<char>(0x82), s8[2]);
    ASSERT_EQ(static_cast<char>(0xe3), s8[3]);
    ASSERT_EQ(static_cast<char>(0x81), s8[4]);
    ASSERT_EQ(static_cast<char>(0x84), s8[5]);
}

TEST(GTestCvtUtf, TestUtf32ToUtf16BE) {
    std::u32string s32;
    std::string s16be = fromUtf32(s32, UTF16BE);
    ASSERT_EQ(0, s16be.length());

    s32 += 0x3042;
    s32 += 0x2000b;
    s16be = fromUtf32(s32, UTF16BE);
    ASSERT_EQ(6, s16be.length());
    ASSERT_EQ(static_cast<char>(0x30), s16be[0]);
    ASSERT_EQ(static_cast<char>(0x42), s16be[1]);
    ASSERT_EQ(static_cast<char>(0xd8), s16be[2]);
    ASSERT_EQ(static_cast<char>(0x40), s16be[3]);
    ASSERT_EQ(static_cast<char>(0xdc), s16be[4]);
    ASSERT_EQ(static_cast<char>(0x0b), s16be[5]);
}

TEST(GTestCvtUtf, TestUtf32ToUtf16LE) {
    std::u32string s32;
    std::string s16le = fromUtf32(s32, UTF16LE);
    ASSERT_EQ(0, s16le.length());

    s32 += 0x3042;
    s32 += 0x2000b;
    s16le = fromUtf32(s32, UTF16LE);
    ASSERT_EQ(6, s16le.length());
    ASSERT_EQ(static_cast<char>(0x42), s16le[0]);
    ASSERT_EQ(static_cast<char>(0x30), s16le[1]);
    ASSERT_EQ(static_cast<char>(0x40), s16le[2]);
    ASSERT_EQ(static_cast<char>(0xd8), s16le[3]);
    ASSERT_EQ(static_cast<char>(0x0b), s16le[4]);
    ASSERT_EQ(static_cast<char>(0xdc), s16le[5]);
}

TEST(GTestCvtUtf, TestUtf32ToUtf32BE) {
    std::u32string s32;
    std::string s32be = fromUtf32(s32, UTF32BE);
    ASSERT_EQ(0, s32be.length());

    s32 += 0x3042;
    s32 += 0x2000b;
    s32be = fromUtf32(s32, UTF32BE);
    ASSERT_EQ(8, s32be.length());
    ASSERT_EQ(static_cast<char>(0x00), s32be[0]);
    ASSERT_EQ(static_cast<char>(0x00), s32be[1]);
    ASSERT_EQ(static_cast<char>(0x30), s32be[2]);
    ASSERT_EQ(static_cast<char>(0x42), s32be[3]);
    ASSERT_EQ(static_cast<char>(0x00), s32be[4]);
    ASSERT_EQ(static_cast<char>(0x02), s32be[5]);
    ASSERT_EQ(static_cast<char>(0x00), s32be[6]);
    ASSERT_EQ(static_cast<char>(0x0b), s32be[7]);
}

TEST(GTestCvtUtf, TestUtf32ToUtf32LE) {
    std::u32string s32;
    std::string s32le = fromUtf32(s32, UTF32LE);
    ASSERT_EQ(0, s32le.length());

    s32 += 0x3042;
    s32 += 0x2000b;
    s32le = fromUtf32(s32, UTF32LE);
    ASSERT_EQ(8, s32le.length());
    ASSERT_EQ(static_cast<char>(0x42), s32le[0]);
    ASSERT_EQ(static_cast<char>(0x30), s32le[1]);
    ASSERT_EQ(static_cast<char>(0x00), s32le[2]);
    ASSERT_EQ(static_cast<char>(0x00), s32le[3]);
    ASSERT_EQ(static_cast<char>(0x0b), s32le[4]);
    ASSERT_EQ(static_cast<char>(0x00), s32le[5]);
    ASSERT_EQ(static_cast<char>(0x02), s32le[6]);
    ASSERT_EQ(static_cast<char>(0x00), s32le[7]);
}

TEST(GTestCvtUtf, TestUtf32ToUtf16) {
    std::u32string s32;
    std::u16string s16 = utf32ToUtf16(s32);
    ASSERT_EQ(0, s16.length());

    s32 += 0x3042;
    s32 += 0x2000b;
    s16 = utf32ToUtf16(s32);
    ASSERT_EQ(3, s16.length());
    ASSERT_EQ(static_cast<char16_t>(0x3042), s16[0]);
    ASSERT_EQ(static_cast<char16_t>(0xd840), s16[1]);
    ASSERT_EQ(static_cast<char16_t>(0xdc0b), s16[2]);
}

}  // namespace glue
}  // namespace libj
