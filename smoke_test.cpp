//
// Created by Александр Чори on 13.01.2020.
// Changed by Pavel Gromov on 14.01.2020
//

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <exception>
#include <iostream>
#include <vector>

#include "utils.hpp"

#include "vector.hpp"

namespace current_namespace {
    using namespace exam;
}

#define CUSTOM_ALLOCATOR_SUPPORT false
#define RANDOM_ACCESS_ITERATOR_SUPPORT false

void test_constructor() {
    current_namespace::vector<int> vec1;
    current_namespace::vector<int> vec2(10);

    for (std::size_t i = 0; i < vec2.size(); ++i) {
        assert(vec2[i] == 0);
    }
}

void test_constructor_with_default_value() {
    current_namespace::vector<int> fwd(10, 3);

    for (std::size_t i = 0; i < fwd.size(); ++i) {
        assert(fwd[i] == 3);
    }
}

//     Should be compile error
//void test_constructor_without_default() {
//    struct NoDefaultConstructor {
//        NoDefaultConstructor() = delete;
//    };
//    current_namespace::vector<NoDefaultConstructor> vec3(10);
//}

void test_screamer() {
    struct Screamer {
        Screamer() {
            std::cout << "I was born" << std::endl;
        }

        virtual ~Screamer() {
            std::cout << "I died" << std::endl;
        }
    };

    current_namespace::vector<Screamer> arr;

    for (std::size_t i = 0; i < 10; ++i) {
        arr.push_back({});
    }
}

void test_erase() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << vec.capacity() << std::endl;
    std::cout << vec.size() << std::endl;
    vec.erase(vec.begin());
    vec.erase(vec.begin());

    std::cout << vec.capacity() << std::endl;
}

void test_A() {
    struct A {
        int a;

        A(int v) : a(v) {}

        ~A() {
            std::cout << a << std::endl;
        }
    };

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << " -------------- " << std::endl;
    vec.erase(vec.begin());
    std::cout << " -------------- " << std::endl;
}

void test_operator_equal() {
    current_namespace::vector<double> vec1;
    current_namespace::vector<double> vec2(15);

    for (std::size_t i = 0; i < 15; ++i) {
        vec2[i] = i * 0.1;
    }

    vec1 = vec2;

    for (std::size_t i = 0; i < 15; ++i) {
        assert(std::abs(vec1[i] - vec2[i]) < std::numeric_limits<double>::epsilon());
    }

    current_namespace::vector<double> vec3(vec1);

    for (std::size_t i = 0; i < 15; ++i) {
        assert(std::abs(vec1[i] - vec3[i]) < std::numeric_limits<double>::epsilon());
    }
}

void test_size_capacity() {
    current_namespace::vector<std::vector<int>> arr;

    assert(arr.size() == 0);
    assert(arr.capacity() == 0);
    assert(arr.empty());

    for (std::size_t i = 0; i < 700; ++i) {
        arr.push_back({});
    }

    std::size_t capacity = arr.capacity();

    arr.clear();

    assert(arr.capacity() == capacity);
}

void test_shrink_to_fit() {
    current_namespace::vector<int> vec;

    for (std::size_t i = 0; i < 10000; ++i) {
        vec.push_back(i);
    }

    for (std::size_t i = 0; i < 500; ++i) {
        vec.pop_back();
    }

    vec.shrink_to_fit();
    assert(vec.size() == vec.capacity());

    for (std::size_t i = 0; i < 9500; ++i) {
        assert(vec[i] == int(i));
    }
}

void test_at() {
    current_namespace::vector<int> vec(100);

    for (std::size_t i = 0; i < vec.size(); ++i) {
        vec[i] = i;
    }

    for (std::size_t i = 0; i < vec.size(); ++i) {
        assert(vec[i] == vec.at(i));
    }
}

void test_swap() {
    current_namespace::vector<int> fwd(10);
    current_namespace::vector<int> bck(10);

    for (std::size_t i = 0; i < fwd.size(); ++i) {
        fwd[i] = i;
    }

    for (std::size_t i = bck.size(); i > 0; --i) {
        bck[10 - i] = i;
    }

    swap(fwd, bck);

    for (std::size_t i = 0; i < fwd.size(); ++i) {
        assert(bck[i] == int(i));
        assert(fwd[i] == int(10 - i));
    }
}

int main() {

#if CUSTOM_ALLOCATOR_SUPPORT
    {
        current_namespace::vector<int, std::allocator<int>> vec;

        for (std::size_t i = 0; i < 10000; ++i) {
            vec.push_back(i);
        }

        for (std::size_t i = 0; i < 500; ++i) {
            vec.pop_back();
        }

        vec.shrink_to_fit();
        assert(vec.size() == vec.capacity());

        for (std::size_t i = 0; i < 9500; ++i) {
            assert(vec[i] == i);
        }
    }
#endif


#if RANDOM_ACCESS_ITERATOR_SUPPORT
    {
        current_namespace::vector<int> fwd(10, 25);

        for (auto &x: fwd) {
            assert(x == 25);
        }

        fwd[10] = 60;
        sort(std::begin(fwd), std::end(fwd));
    }
#endif
    test_constructor();
    test_constructor_with_default_value();
    test_screamer();
    test_operator_equal();
    test_size_capacity();
    test_shrink_to_fit();
    test_at();
    test_swap();

    std::cout << "All tests have passed!" << std::endl;

    return 0;
}
