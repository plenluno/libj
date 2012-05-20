// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_FILE_INPUT_STREAM_H_
#define LIBJ_FILE_INPUT_STRESM_H_

#include "libj/input_stream.h"
#include "libj/string.h"

namespace libj {

class FileInputStream : LIBJ_INPUT_STREAM(FileInputStream)
 public:
    static Ptr create(String::CPtr path);
};

}  // namespace libj

#endif  // LIBJ_FILE_INPUT_STREAM_H_