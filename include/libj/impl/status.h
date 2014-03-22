// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_STATUS_H_
#define LIBJ_IMPL_STATUS_H_

#define LIBJ_STATUS_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Status>::id() || LIBJ_IMMUTABLE_INSTANCEOF(ID))

#ifdef LIBJ_USE_CXX11
namespace std {
#else
namespace boost {
#endif
    template <>
    struct hash<libj::Status::Code> {
        std::size_t operator()(const libj::Status::Code& key) const {
            return static_cast<std::size_t>(key);
        }
    };
}

#endif  // LIBJ_IMPL_STATUS_H_
