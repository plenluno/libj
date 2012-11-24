// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_SET_H_
#define LIBJ_DETAIL_SET_H_

#include "libj/set.h"

#include "./generic_set.h"

namespace libj {
namespace detail {

template<typename I>
class Set : public GenericSet<Value, I> {
 public:
    Boolean add(const Value& v) {
        return this->addTyped(v);
    }

    Boolean remove(const Value& v) {
        return this->removeTyped(v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_SET_H_
