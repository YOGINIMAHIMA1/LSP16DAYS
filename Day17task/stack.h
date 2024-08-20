#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template<typename T>
class Stack {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Stack(size_t initial_capacity = 2) : capacity(initial_capacity), size(0) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    void pop() {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        --size;
    }

    T& peek() const {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[size - 1];
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

#endif // STACK_H
