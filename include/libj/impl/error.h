// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_ERROR_H_
#define LIBJ_IMPL_ERROR_H_

#define LIBJ_ERROR_INSTANCEOF(ID) \
    (ID == libj::Type<libj::Error>::id() || LIBJ_STATUS_INSTANCEOF(ID))

#ifdef LIBJ_USE_CXX11
namespace std {
#else
namespace boost {
#endif
    template <>
    struct hash<libj::Error::Code> {
        std::size_t operator()(const libj::Error::Code& key) const {
            return static_cast<std::size_t>(key);
        }
    };
}

#endif  // LIBJ_IMPL_ERROR_H_
