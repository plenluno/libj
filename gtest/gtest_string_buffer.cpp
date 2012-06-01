// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string_buffer.h>

namespace libj {

TEST(GTestStringBuffer, TestToString) {
    StringBuffer::Ptr sb = StringBuffer::create();
    String::CPtr s1 = String::create("abc");
    String::CPtr s2 = String::create("def");
    String::CPtr s3 = String::create("abcdef");
    sb->append(s1);
    sb->append(s2);
    ASSERT_EQ(sb->toString()->compareTo(s3), 0);
}

TEST(GTestStringBuffer, TestToStringMb) {
    const char aiu8[] = {
        0xe3, 0x81, 0x82, 0xe3, 0x81, 0x84, 0xe3, 0x81,
        0x86, 0xe3, 0x81, 0x88, 0xe3, 0x81, 0x8a,       // あいうえお
        0
    };
    const char u8[] = {
        0x31, 0x32, 0x33,                               // 123
        0xe3, 0x81, 0x82, 0xe3, 0x81, 0x84, 0xe3, 0x81,
        0x86, 0xe3, 0x81, 0x88, 0xe3, 0x81, 0x8a,       // あいうえお
        0x34, 0x35, 0x36,                               // 456
        0
    };
    StringBuffer::Ptr sb = StringBuffer::create();
    String::CPtr s1 = String::create("123");
    String::CPtr s2 = String::create(aiu8, String::UTF8);
    String::CPtr s3 = String::create("456");
    String::CPtr e0 = String::create("");
    String::CPtr e1 = s1;
    String::CPtr e2 = String::create(u8, String::UTF8, 8);
    String::CPtr e3 = String::create(u8, String::UTF8);

    ASSERT_EQ(sb->length(), 0);
    ASSERT_EQ(sb->toString()->compareTo(e0), 0);
    sb->append(s1);
    ASSERT_EQ(sb->length(), 3);
    ASSERT_EQ(sb->toString()->compareTo(e1), 0);
    sb->append(s2);
    ASSERT_EQ(sb->length(), 8);
    ASSERT_EQ(sb->toString()->compareTo(e2), 0);
    sb->append(s3);
    ASSERT_EQ(sb->length(), 11);
    ASSERT_EQ(sb->toString()->compareTo(e3), 0);
}

TEST(GTestStringBuffer, TestAppendManyTimes) {
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
    StringBuffer::Ptr sb = StringBuffer::create();
    for (int i = 0; i < 100; i++) {
        sb->append(s1);
        sb->append(s2);
        exp = exp->concat(s1)->concat(s2);
    }
    ASSERT_EQ(sb->toString()->compareTo(exp), 0);
}

#ifdef LIBJ_USE_SP
TEST(GTestStringBuffer, TestUseCount) {
    StringBuffer::CPtr p = StringBuffer::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
