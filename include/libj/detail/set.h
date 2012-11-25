// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_SET_H_
#define LIBJ_DETAIL_SET_H_

#include "./generic_set.h"

namespace libj {
namespace detail {

template<typename I>
class Set : public GenericSet<Value, I> {
 public:
    Boolean add(const Value& v) {
        return GenericSet<Value, I>::addTyped(v);
    }

    Boolean remove(const Value& v) {
        return GenericSet<Value, I>::removeTyped(v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_SET_H_
