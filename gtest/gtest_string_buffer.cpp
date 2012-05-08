// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string_buffer.h>

namespace libj {

TEST(GTestStringBuffer, TestToString) {
    Type<StringBuffer>::Ptr sb = StringBuffer::create();
    Type<String>::Cptr s1 = String::create("abc");
    Type<String>::Cptr s2 = String::create("def");
    Type<String>::Cptr s3 = String::create("abcdef");
    sb->append(s1);
    sb->append(s2);
    ASSERT_EQ(sb->toString()->compareTo(s3), 0);
}

#ifdef LIBJ_USE_SP
TEST(GTestStringBuffer, TestUseCount) {
    Type<StringBuffer>::Cptr p = StringBuffer::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
