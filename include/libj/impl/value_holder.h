// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_VALUE_HOLDER_H_
#define LIBJ_IMPL_VALUE_HOLDER_H_

#define LIBJ_VALUE_HOLDER_INSTANCEOF(ID) \
    (ID == libj::Type<libj::ValueHolder>::id() || LIBJ_MUTABLE_INSTANCEOF(ID))

namespace libj {

template<typename T>
inline typename Type<T>::Ptr ValueHolder::getPtr() const {
    return toPtr<T>(get());
}

template<typename T>
inline typename Type<T>::CPtr ValueHolder::getCPtr() const {
    return toCPtr<T>(get());
}

}  // namespace libj

#endif  // LIBJ_IMPL_VALUE_HOLDER_H_
