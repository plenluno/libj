#!/bin/sh
tools/cpplint/cpplint.py --filter=-runtime/explicit,-readability/streams --prefix=libj `find include src btest gtest -type f`
