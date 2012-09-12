// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/string.h>

namespace libj {

TEST(GTestConsole, TestConsole1) {
    // no assert
    console::log("log");
    console::info("info");
    console::warn("warn");
    console::error("error");
    console::write("write\n");
}

TEST(GTestConsole, TestConsole2) {
    // no assert
    console::log(String::create("log"));
    console::info(String::create("info"));
    console::warn(String::create("warn"));
    console::error(String::create("error"));
    console::write(String::create("write\n"));
}

}  // namespace libj
