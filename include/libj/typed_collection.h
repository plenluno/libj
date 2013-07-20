// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_COLLECTION_H_
#define LIBJ_TYPED_COLLECTION_H_

#include <libj/typed_iterator.h>

namespace libj {

template<typename L, typename T>
class TypedCollection : public L {
 public:
    virtual Boolean addTyped(const T& t) = 0;

    virtual Boolean removeTyped(const T& t) = 0;

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const = 0;
};

}  // namespace libj

#define LIBJ_TYPED_COLLECTION(L, T) \
    public detail::Generic##L<TypedCollection<L, T>, T> { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(Typed##L, L)

#endif  // LIBJ_TYPED_COLLECTION_H_
