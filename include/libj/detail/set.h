// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_SET_H_
#define LIBJ_DETAIL_SET_H_

#include <libj/detail/generic_set.h>

namespace libj {
namespace detail {

template<typename I>
class Set : public GenericSet<I, Value> {
 public:
    Boolean add(const Value& v) {
        return GenericSet<I, Value>::addTyped(v);
    }

    Boolean remove(const Value& v) {
        return GenericSet<I, Value>::removeTyped(v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_SET_H_
