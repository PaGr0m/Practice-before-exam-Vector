//
// Created by Александр Чори on 13.01.2020.
//

#ifndef PRACTICE_BEFORE_EXAM_VECTOR_UTILS_HPP
#define PRACTICE_BEFORE_EXAM_VECTOR_UTILS_HPP


#include <cassert>

template<typename ExceptionType, typename Func>
void assert_throws(Func f) {
    try {
        f();
    } catch (ExceptionType const &e) {
        assert(true);
    }

    assert(false);
}


#endif //PRACTICE_BEFORE_EXAM_VECTOR_UTILS_HPP
