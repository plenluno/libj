// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_object.h>

namespace libj {

class XObj : LIBJ_JS_OBJECT(XObj)
 public:
    static Ptr create() {
        Ptr p(new XObj());
        return p;
    }

 private:
    JsObject::Ptr jo_;

    XObj() : jo_(JsObject::create()) {}

    LIBJ_JS_OBJECT_IMPL(jo_);
};


TEST(GTestObject, TestGetCPtr) {
    JsObject::Ptr obj = JsObject::create();
    String::CPtr abc = String::create("abc");
    obj->put(abc, abc);
    ASSERT_EQ(obj->getCPtr<String>(abc)->compareTo(abc), 0);

    XObj::Ptr xobj = XObj::create();
    xobj->put(abc, abc);
    ASSERT_EQ(xobj->getCPtr<String>(abc)->compareTo(abc), 0);
}

}  // namespace libj
