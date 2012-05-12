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

#ifdef LIBJ_USE_SP
TEST(GTestStringBuffer, TestUseCount) {
    StringBuffer::CPtr p = StringBuffer::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
