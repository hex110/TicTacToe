#ifndef SQUARE_CPP
#define SQUARE_CPP
#include <iostream>
#include <memory>

// type: factory
template <typename T>
class Square {
public:
    virtual T getSquare() const = 0;
    virtual std::unique_ptr<Square<T>> clone() const = 0;
};

template <typename T>
class X : public Square<T> {
public:
    T getSquare() const override { return 'X'; }
    std::unique_ptr<Square<T>> clone() const override {
        return std::make_unique<X<T>>(*this);
    }
};

template <typename T>
class O : public Square<T> {
public:
    T getSquare() const override { return 'O'; }
    std::unique_ptr<Square<T>> clone() const override {
        return std::make_unique<O<T>>(*this);
    }
};

class SquareFactory {
public:
    static std::unique_ptr<Square<char>> createSquare(char symbol) {
        if (symbol == 'X') {
            return std::make_unique<X<char>>();
        } else if (symbol == 'O') {
            return std::make_unique<O<char>>();
        } else {
            throw std::invalid_argument("Invalid square symbol");
        }
        return nullptr;
    }
};

#endif