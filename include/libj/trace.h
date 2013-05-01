// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_TRACE_H_
#define LIBJ_TRACE_H_

#include <libj/config.h>

#ifdef LIBJ_DEBUG

namespace libj {
namespace trace {

void on();

void off();

void include(const char* prefix);

void exclude(const char* prefix);

}  // namespace trace
}  // namespace libj

#endif

#endif  // LIBJ_TRACE_H_
