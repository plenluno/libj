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

    setForegroundColor(NORMAL, DEFAULT);
    setForegroundColor(DEBUG, BLACK);
    setForegroundColor(INFO, RED);
    setForegroundColor(WARNING, GREEN);
    setForegroundColor(ERROR, YELLOW);

    log("log");
    debug("debug");
    info("info");
    warn("warn");
    error("error");

    setForegroundColor(NORMAL, DEFAULT);
    setForegroundColor(DEBUG, DEFAULT);
    setForegroundColor(INFO, DEFAULT);
    setForegroundColor(WARNING, DEFAULT);
    setForegroundColor(ERROR, DEFAULT);
}

TEST(GTestConsole, TestSetBackgroundColor) {
    // no assert

    setBackgroundColor(NORMAL, DEFAULT);
    setBackgroundColor(DEBUG, BLUE);
    setBackgroundColor(INFO, MAGENTA);
    setBackgroundColor(WARNING, CYAN);
    setBackgroundColor(ERROR, WHITE);

    log(String::create("log"));
    debug(String::create("debug"));
    info(String::create("info"));
    warn(String::create("warn"));
    error(String::create("error"));

    setBackgroundColor(NORMAL, DEFAULT);
    setBackgroundColor(DEBUG, DEFAULT);
    setBackgroundColor(INFO, DEFAULT);
    setBackgroundColor(WARNING, DEFAULT);
    setBackgroundColor(ERROR, DEFAULT);
}

TEST(TestConsole, TestPrintf) {
    // no assert

    printf(INFO, "%d %d %d\n", 1, 2, 3);
    printf(DEBUG, "%s\n", "printf");
}

TEST(TestConsole, TestPrintv) {
    // no assert

    Value a = 1;
    Value b = 2;
    Value c = 3;
    printv(NORMAL, "%v %v %v\n", a, b, c);
    printv(ERROR, "%v\n", String::create("printv"));
}

TEST(TestConsole, TestSetLevel) {
    setLevel(NORMAL);
    ASSERT_FALSE(info(String::create("info")));
    ASSERT_TRUE(log(String::create("log")));

    setLevel(OFF);
    ASSERT_FALSE(error(String::create("error")));

    setLevel(DEBUG);
}

}  // namespace console
}  // namespace libj
