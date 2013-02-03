// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/exception.h>

#ifdef LIBJ_USE_EXCEPTION

namespace libj {

class Exception::Impl {
 public:
    Impl(Error::Code code)
        : err_(Error::create(code))
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Impl(String::CPtr message)
        : err_(Error::create(Error::ANY))
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Impl(Error::Code code, String::CPtr message)
        : err_(Error::create(code, message))
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Impl(Error::Code code, const char* file, const char* func, int line)
        : err_(Error::create(code))
        , file_(String::create(file))
        , func_(String::create(func))
        , line_(line) {}

    Int code() const {
        return err_ ? err_->code() : Error::ANY;
    }

    String::CPtr message() const {
        return err_ ? err_->message() : String::null();
    }

    String::CPtr file() const {
        return file_;
    }

    String::CPtr function() const {
        return func_;
    }

    Int line() const {
        return line_;
    }

 private:
    Error::CPtr err_;
    String::CPtr file_;
    String::CPtr func_;
    Int line_;
};

Exception::Exception(Error::Code code)
    : impl_(new Impl(code)) {}

Exception::Exception(String::CPtr message)
    : impl_(new Impl(message)) {}

Exception::Exception(Error::Code code, String::CPtr message)
    : impl_(new Impl(code, message)) {}

Exception::Exception(
    Error::Code code, const char* file, const char* func, int line)
    : impl_(new Impl(code, file, func, line)) {}

Exception::~Exception() throw() {
    delete impl_;
}

Int Exception::code() const {
    return impl_->code();
}

String::CPtr Exception::message() const {
    return impl_->message();
}

String::CPtr Exception::file() const {
    return impl_->file();
}

String::CPtr Exception::function() const {
    return impl_->function();
}

Int Exception::line() const {
    return impl_->line();
}

}  // namespace libj

#endif  // LIBJ_USE_EXCEPTION
