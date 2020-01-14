//
// Created by Pavel Gromov on 14.01.2020.
//

#ifndef PRACTICE_BEFORE_EXAM_VECTOR_VECTOR_HPP
#define PRACTICE_BEFORE_EXAM_VECTOR_VECTOR_HPP

#include <exception>

namespace exam {

    template<typename Type>
    struct vector {

        using value_type = Type;
        using size_type = size_t;

        vector() : data_(nullptr),
                   size_(0),
                   capacity_(0) {}

        explicit vector(size_t size) : size_(size), capacity_(size) {
            data_ = new Type[size_]{};
        }

        vector(size_t size, Type num) : size_(size), capacity_(size) {
            data_ = new Type[size_];

            for (size_t i = 0; i < size; ++i)
                data_[i] = num;
        }

        vector(const vector<Type> &other)
                : size_(other.size_),
                  capacity_(other.capacity_) {
            data_ = new Type[capacity_]{};
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }

        ~vector() {
            delete[] data_;
        }

        vector<Type> &operator=(vector<Type> other) {
            swap(other);
            return *this;
        }

        void swap(vector<Type> &other) {
            std::swap(data_, other.data_);
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
        }

        Type *data() {
            return data_;
        }

        const Type *data() const {
            return data_;
        }

        bool empty() const {
            return size_ == 0;
        }

        size_t size() const {
            return size_;
        }

        size_t capacity() const {
            return capacity_;
        }

        Type &operator[](size_t idx) {
            return data_[idx];
        }

        const Type &operator[](size_t idx) const {
            return data_[idx];
        }

        const Type &at(size_t idx) const {
            if (idx > size_ || size_ == 0)
                throw std::out_of_range("Index out of range");

            return data_[idx];
        }

        Type &at(size_t idx) {
            return const_cast<Type &>(std::as_const(*this).at(idx));
        }

        const Type &front() const {
            return at(0);
        }

        Type &front() {
            return const_cast<Type &>(std::as_const(*this).front());
        }

        const Type &back() const {
            return at(size_ - 1);
        }

        Type &back() {
            return const_cast<Type &>(std::as_const(*this).back());
        }

        void reserve(size_t new_capacity) {
            if (capacity_ >= new_capacity)
                return;

            relocate(size_, new_capacity);
        }

        void shrink_to_fit() {
            if (capacity_ == size_)
                return;

            relocate(size_, size_);
        }

        void clear() {
            delete[] data_;

            data_ = new Type[capacity_]{};
            size_ = 0;
        }

        void insert(size_t idx, Type value) {
            if (idx >= size_)
                throw std::out_of_range("Index out of range (insert)");

            if (size_ + 1 > capacity_) {
                relocate(size_ + 1, next_capacity_value());

                for (size_t i = size_ + 1; i > idx; --i) {
                    data_[i + 1] = data_[i];
                }

                data_[idx] = value;

                return;
            }

            for (size_t i = size_ + 1; i > idx; --i) {
                data_[i + 1] = data_[i];
            }

            data_[idx] = value;
            ++size_;
        }

        void erase(size_t idx) {
            if (idx >= size_)
                throw std::out_of_range("Index out of range (erase)");

            for (size_t i = idx; i < size_; ++i) {
                data_[i] = data_[i + 1];
            }

            --size_;
        }

        void push_back(const Type &value) {
            if (size_ + 1 > capacity_) {
                relocate(size_ + 1, next_capacity_value());
                data_[size_ - 1] = value;
                return;
            }

            ++size_;
            data_[size_ - 1] = value;
        }

        void pop_back() {
            if (size_ == 0)
                throw std::out_of_range("Index out of range (pop_back)");

            --size_;
        }

        void resize(size_t new_size) {
            if (capacity_ > new_size) {
                capacity_ = new_size;
                size_ = new_size;
                return;
            }

            relocate(new_size, new_size);
        }

    private:
        void relocate(size_t new_size, size_t new_capacity) {
            Type *new_data = new Type[new_capacity]{};

            for (size_t i = 0; i < size_; ++i)
                new_data[i] = data_[i];

            delete[] data_;

            data_ = new_data;
            size_ = new_size;
            capacity_ = new_capacity;
        }

        size_t next_capacity_value() {
            if (capacity_ == 0)
                return 1;

            return capacity_ * 2;
        }

        struct iterator : std::iterator<std::random_access_iterator_tag, Type> {
            using pointer = typename std::iterator<std::random_access_iterator_tag, Type>::pointer;
            using reference = typename std::iterator<std::random_access_iterator_tag, Type>::reference;
            using difference_type = typename std::iterator<std::random_access_iterator_tag, Type>::difference_type;

        private:
            explicit iterator(vector<Type> *container)
                    : container_(container),
                      idx_(0) {}

            iterator(vector<Type> *container, size_t idx)
                    : container_(container),
                      idx_(idx) {}

        private:
            vector<Type> &container_;
            size_t idx_;
        };

    private:
        Type *data_;

        size_t size_;
        size_t capacity_;
    };

    template<typename Type>
    void swap(vector<Type> &lhs, vector<Type> &rhs) {
        lhs.swap(rhs);
    }

    template<typename Type, typename Comparator>
    bool compare(const vector<Type> &lhs, const vector<Type> &rhs, Comparator comparator) {
        return std::lexicographical_compare(lhs.data(), lhs.data() + lhs.size(),
                                            rhs.data(), rhs.data() + rhs.size(),
                                            comparator);
    }
}

#endif //PRACTICE_BEFORE_EXAM_VECTOR_VECTOR_HPP
