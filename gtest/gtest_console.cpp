// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/string.h>

namespace libj {
namespace console {

TEST(GTestConsole, TestConsole1) {
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

TEST(GTestConsole, TestConsole2) {
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

TEST(TestConsole, TestConsole3) {
    // no assert

    printf(DEBUG, "%s\n", "printf");
    printv(ERROR, "%v\n", String::create("printv"));

    Value a = 1;
    Value b = 2;
    Value c = 3;
    printv(NORMAL, "%v %v %v\n", a, b, c);
}

TEST(TestConsole, TestConsole4) {
    setLevel(NORMAL);
    ASSERT_FALSE(info(String::create("info")));
    ASSERT_TRUE(log(String::create("log")));

    setLevel(OFF);
    ASSERT_FALSE(error(String::create("error")));

    setLevel(DEBUG);
}

}  // namespace console
}  // namespace libj
