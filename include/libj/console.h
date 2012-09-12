// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_CONSOLE_H_
#define LIBJ_CONSOLE_H_

#include "libj/value.h"

namespace libj {
namespace console {

void log(const char* s);
void info(const char* s);
void warn(const char* s);
void error(const char* s);
void write(const char* s);

Boolean log(const Value& val);
Boolean info(const Value& val);
Boolean warn(const Value& val);
Boolean error(const Value& val);
Boolean write(const Value& val);

}  // namespace console
}  // namespace libj

#endif  // LIBJ_CONSOLE_H_
