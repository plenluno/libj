// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string_builder.h>

#pragma GCC diagnostic ignored "-Wnarrowing"

namespace libj {

TEST(GTestStringBuilder, TestCharAt) {
    StringBuilder::Ptr sb = StringBuilder::create();
    String::CPtr empty = String::create();
    String::CPtr abc = String::create("abc");
    sb->append(empty);
    sb->append(abc);
    ASSERT_EQ('c', sb->charAt(2));
}

TEST(GTestStringBuilder, TestToString) {
    StringBuilder::Ptr sb = StringBuilder::create();
    String::CPtr s1 = String::create("abc");
    String::CPtr s2 = String::create("def");
    String::CPtr s3 = String::create("abcdef");
    sb->append(s1);
    sb->append(s2);
    ASSERT_TRUE(sb->toString()->equals(s3));
    ASSERT_TRUE(sb->toString()->equals(s3));
}

TEST(GTestStringBuilder, TestToString2) {
    const char aiu8[] = {
        0xe3, 0x81, 0x82,  // a
        0xe3, 0x81, 0x84,  // i
        0xe3, 0x81, 0x86,  // u
        0xe3, 0x81, 0x88,  // e
        0xe3, 0x81, 0x8a,  // o
        0
    };
    const char u8[] = {
        0x31, 0x32, 0x33,  // 1 2 3
        0xe3, 0x81, 0x82,  // a
        0xe3, 0x81, 0x84,  // i
        0xe3, 0x81, 0x86,  // u
        0xe3, 0x81, 0x88,  // e
        0xe3, 0x81, 0x8a,  // o
        0x34, 0x35, 0x36,  // 4 5 6
        0
    };

    StringBuilder::Ptr sb = StringBuilder::create();
    String::CPtr s1 = String::create("123");
    String::CPtr s2 = String::create(aiu8, String::UTF8);
    String::CPtr s3 = String::create("456");
    String::CPtr e0 = String::create("");
    String::CPtr e1 = s1;
    String::CPtr e2 = String::create(u8, String::UTF8, NO_SIZE, 8);
    String::CPtr e3 = String::create(u8, String::UTF8);

    ASSERT_EQ(0, sb->length());
    ASSERT_TRUE(sb->toString()->equals(e0));

    sb->append(s1);
    ASSERT_EQ(3, sb->length());
    ASSERT_TRUE(sb->toString()->equals(e1));

    sb->append(s2);
    ASSERT_EQ(8, sb->length());
    ASSERT_TRUE(sb->toString()->equals(e2));

    sb->append(s3);
    ASSERT_EQ(11, sb->length());
    ASSERT_TRUE(sb->toString()->equals(e3));
}

TEST(GTestStringBuilder, TestAppendBoolean) {
    StringBuilder::Ptr sb = StringBuilder::create();
    sb->append(true);
    sb->append(false);
    ASSERT_TRUE(sb->toString()->equals(String::create("truefalse")));
}

TEST(GTestStringBuilder, TestAppendManyTimes) {
    const char a[] = "abcde";
    const char u[] = {
        0xe7, 0x8c, 0xab, 0xe3, 0x81, 0xa8, 0xe6, 0x9a,
        0xae, 0xe3, 0x82, 0x89, 0xe3, 0x81, 0x97, 0xe3,
        0x81, 0x9f, 0xe3, 0x81, 0x84,   // 猫と暮らしたい
        0
    };

    String::CPtr s1 = String::create(a);
    String::CPtr s2 = String::create(u, String::UTF8);
    String::CPtr exp = String::create("");
    StringBuilder::Ptr sb = StringBuilder::create();
    for (int i = 0; i < 100; i++) {
        sb->append(s1);
        sb->append(s2);
        exp = exp->concat(s1)->concat(s2);
    }
    ASSERT_TRUE(sb->toString()->equals(exp));
}

TEST(GTestStringBuilder, TestAppendChar) {
    StringBuilder::Ptr sb = StringBuilder::create();
    ASSERT_EQ(sb, sb->appendChar('a'));
    ASSERT_EQ(sb, sb->appendChar('1'));
    ASSERT_TRUE(sb->toString()->equals(String::create("a1")));
}

TEST(GTestStringBuilder, TestAppendCStr) {
    StringBuilder::Ptr sb = StringBuilder::create();
    ASSERT_EQ(sb, sb->appendCStr("abc"));
    ASSERT_EQ(sb, sb->appendCStr(NULL));
    ASSERT_EQ(sb, sb->appendCStr("123"));
    ASSERT_TRUE(sb->toString()->equals(String::create("abcnull123")));
}

}  // namespace libj
