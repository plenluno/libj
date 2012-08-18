// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"

namespace libj {

class ErrorImpl : public Error {
 private:
    static const String::CPtr MSG_TIMEOUT;
    static const String::CPtr MSG_ILLEGAL_ARGUMENT;
    static const String::CPtr MSG_ILLEGAL_DATA_FORMAT;
    static const String::CPtr MSG_ILLEGAL_REQUEST;
    static const String::CPtr MSG_ILLEGAL_RESPONSE;
    static const String::CPtr MSG_ILLEGAL_STATE;
    static const String::CPtr MSG_ILLEGAL_TYPE;
    static const String::CPtr MSG_INDEX_OUT_OF_BOUNDS;
    static const String::CPtr MSG_NO_SUCH_ELEMENT;
    static const String::CPtr MSG_NO_SUCH_FIELD;
    static const String::CPtr MSG_NO_SUCH_METHOD;
    static const String::CPtr MSG_NULL_POINTER;
    static const String::CPtr MSG_UNSUPPORTED_VERSION;
    static const String::CPtr MSG_UNSUPPORTED_OPERATION;

 private:
    Status::CPtr status_;

    ErrorImpl(Int code, String::CPtr msg)
        : status_(Status::create(code, msg)) {}

 public:
    static CPtr create(Int code) {
        if (code < ANY || code >= END_OF_CODE) {
            return null();
        } else {
            String::CPtr msg;
            switch (code) {
            case TIMEOUT:
                msg = MSG_TIMEOUT;
                break;
            case ILLEGAL_ARGUMENT:
                msg = MSG_ILLEGAL_ARGUMENT;
                break;
            case ILLEGAL_DATA_FORMAT:
                msg = MSG_ILLEGAL_DATA_FORMAT;
                break;
            case ILLEGAL_REQUEST:
                msg = MSG_ILLEGAL_REQUEST;
                break;
            case ILLEGAL_RESPONSE:
                msg = MSG_ILLEGAL_RESPONSE;
                break;
            case ILLEGAL_STATE:
                msg = MSG_ILLEGAL_STATE;
                break;
            case ILLEGAL_TYPE:
                msg = MSG_ILLEGAL_TYPE;
                break;
            case INDEX_OUT_OF_BOUNDS:
                msg = MSG_INDEX_OUT_OF_BOUNDS;
                break;
            case NO_SUCH_ELEMENT:
                msg = MSG_NO_SUCH_ELEMENT;
                break;
            case NO_SUCH_FIELD:
                msg = MSG_NO_SUCH_FIELD;
                break;
            case NO_SUCH_METHOD:
                msg = MSG_NO_SUCH_METHOD;
                break;
            case NULL_POINTER:
                msg = MSG_NULL_POINTER;
                break;
            case UNSUPPORTED_VERSION:
                msg = MSG_UNSUPPORTED_VERSION;
                break;
            case UNSUPPORTED_OPERATION:
                msg = MSG_UNSUPPORTED_OPERATION;
                break;
            default:
                msg = String::null();
            }
            CPtr p(new ErrorImpl(code, msg));
            return p;
        }
    }

    static CPtr create(Int code, String::CPtr msg) {
        if (code < ANY || code >= END_OF_CODE) {
            return null();
        } else {
            CPtr p(new ErrorImpl(code, msg));
            return p;
        }
    }

    LIBJ_STATUS_IMPL(status_);
};

Error::CPtr Error::create(Int code) {
    return ErrorImpl::create(code);
}

Error::CPtr Error::create(Int code, String::CPtr msg) {
    return ErrorImpl::create(code, msg);
}

const String::CPtr ErrorImpl::MSG_TIMEOUT =
    String::create("Timeout");
const String::CPtr ErrorImpl::MSG_ILLEGAL_ARGUMENT =
    String::create("Illegal Argument");
const String::CPtr ErrorImpl::MSG_ILLEGAL_DATA_FORMAT =
    String::create("Illegal Data Format");
const String::CPtr ErrorImpl::MSG_ILLEGAL_REQUEST =
    String::create("Illegal Request");
const String::CPtr ErrorImpl::MSG_ILLEGAL_RESPONSE =
    String::create("Illegal Response");
const String::CPtr ErrorImpl::MSG_ILLEGAL_STATE =
    String::create("Illegal State");
const String::CPtr ErrorImpl::MSG_ILLEGAL_TYPE =
    String::create("Illegal Type");
const String::CPtr ErrorImpl::MSG_INDEX_OUT_OF_BOUNDS =
    String::create("Index Out Of Bounds");
const String::CPtr ErrorImpl::MSG_NO_SUCH_ELEMENT =
    String::create("No Such Element");
const String::CPtr ErrorImpl::MSG_NO_SUCH_FIELD =
    String::create("No Such Field");
const String::CPtr ErrorImpl::MSG_NO_SUCH_METHOD =
    String::create("No Such Method");
const String::CPtr ErrorImpl::MSG_NULL_POINTER =
    String::create("Null Pointer");
const String::CPtr ErrorImpl::MSG_UNSUPPORTED_VERSION =
    String::create("Unsupported Version");
const String::CPtr ErrorImpl::MSG_UNSUPPORTED_OPERATION =
    String::create("Unsupported Operation");

}  // namespace libj
