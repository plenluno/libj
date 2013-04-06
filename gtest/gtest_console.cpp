// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/string.h>

namespace libj {
namespace console {

TEST(GTestConsole, TestLogFunctions) {
    // no assert

    log("log %d", 1);
    debug("debug %f", 2.2);
    info("info %s", "3.33");
    warn("warn %o", 04444);
    error("error %x", 0x55555);
}

TEST(GTestConsole, TestSetForegroundColor) {
    // no assert

    setForegroundColor(LEVEL_NORMAL,  COLOR_DEFAULT);
    setForegroundColor(LEVEL_DEBUG,   COLOR_BLACK);
    setForegroundColor(LEVEL_INFO,    COLOR_RED);
    setForegroundColor(LEVEL_WARNING, COLOR_GREEN);
    setForegroundColor(LEVEL_ERROR,   COLOR_YELLOW);

    log("log");
    debug("debug");
    info("info");
    warn("warn");
    error("error");

    setForegroundColor(LEVEL_NORMAL,  COLOR_DEFAULT);
    setForegroundColor(LEVEL_DEBUG,   COLOR_DEFAULT);
    setForegroundColor(LEVEL_INFO,    COLOR_DEFAULT);
    setForegroundColor(LEVEL_WARNING, COLOR_DEFAULT);
    setForegroundColor(LEVEL_ERROR,   COLOR_DEFAULT);
}

TEST(GTestConsole, TestSetBackgroundColor) {
    // no assert

    setBackgroundColor(LEVEL_NORMAL,  COLOR_DEFAULT);
    setBackgroundColor(LEVEL_DEBUG,   COLOR_BLUE);
    setBackgroundColor(LEVEL_INFO,    COLOR_MAGENTA);
    setBackgroundColor(LEVEL_WARNING, COLOR_CYAN);
    setBackgroundColor(LEVEL_ERROR,   COLOR_WHITE);

    log(String::create("log"));
    debug(String::create("debug"));
    info(String::create("info"));
    warn(String::create("warn"));
    error(String::create("error"));

    setBackgroundColor(LEVEL_NORMAL,  COLOR_DEFAULT);
    setBackgroundColor(LEVEL_DEBUG,   COLOR_DEFAULT);
    setBackgroundColor(LEVEL_INFO,    COLOR_DEFAULT);
    setBackgroundColor(LEVEL_WARNING, COLOR_DEFAULT);
    setBackgroundColor(LEVEL_ERROR,   COLOR_DEFAULT);
}

TEST(TestConsole, TestPrintf) {
    // no assert

    printf(LEVEL_INFO, "%d %d %d\n", 1, 2, 3);
    printf(LEVEL_DEBUG, "%s\n", "printf");
}

TEST(TestConsole, TestPrintv) {
    // no assert

    Value a = 1;
    Value b = 2;
    Value c = 3;
    printv(LEVEL_NORMAL, "%v %v %v\n", a, b, c);
    printv(LEVEL_ERROR, "%v\n", String::create("printv"));
}

TEST(TestConsole, TestAmbibuous0) {
    // no assert

    log(0);
    debug(0);
    info(0);
    warn(0);
    error(0);
}

TEST(TestConsole, TestSetLevel) {
    setLevel(LEVEL_NORMAL);
    ASSERT_FALSE(info(String::create("info")));
    ASSERT_TRUE(log(String::create("log")));

    setLevel(LEVEL_OFF);
    ASSERT_FALSE(error(String::create("error")));

    setLevel(LEVEL_DEBUG);
}

}  // namespace console
}  // namespace libj
