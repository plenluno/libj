// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_OBJECT_H_
#define LIBJ_DETAIL_OBJECT_H_

namespace libj {

inline Object::CPtr Object::null() {
    static LIBJ_NULL_PTR_DEF(Object, nullp);
    return nullp;
}

inline Boolean Object::instanceof(TypeId id) const {
    return id == Type<Object>::id();
}

inline Int Object::compareTo(Object::CPtr that) const {
    if (!that) return TYPE_CMP_NA;

    TypeId thisId = this->type();
    TypeId thatId = that->type();
    if (thisId == thatId) {
        Int diff = static_cast<const Object*>(this) - &(*that);
        if (diff < 0) {
            return -TYPE_CMP_SAME;
        } else if (diff > 0) {
            return TYPE_CMP_SAME;
        } else {
            return 0;
        }
    } else if (this->instanceof(thatId)) {
        return TYPE_CMP_DERIVED;
    } else if (that->instanceof(thisId)) {
        return -TYPE_CMP_DERIVED;
    } else {
        return thisId < thatId
                ? -TYPE_CMP_NOT_DERIVED
                : TYPE_CMP_NOT_DERIVED;
    }
}

inline Boolean Object::equals(Object::CPtr that) const {
    return !compareTo(that);
}

}  // namespace libj

#endif  // LIBJ_DETAIL_OBJECT_H_
