#!/bin/sh
tools/cpplint/cpplint.py --filter=-runtime/explicit,-runtime/references,-runtime/sizeof,-readability/streams,-build/include_order,-build/include_what_you_use --prefix=libj `find include src btest gtest -type f`
