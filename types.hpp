//
// Created by allosker on 11/10/2026.
//

#ifndef UNTITLED1_TYPES_HPP
#define UNTITLED1_TYPES_HPP

#include <memory>
#include <variant>
#include <optional>

enum class Type
{
    None = 0,
    Add, Subtract, Multiply, Divide,
    Exponentiate
};

inline Type char_to_type(char input)
{
    switch (input)
    {
        case '+':
            return Type::Add;
        case '-':
            return Type::Subtract;
        case '*':
            return Type::Multiply;
        case '/':
            return Type::Divide;
        case '^':
            return Type::Exponentiate;

        default:
            return Type::None;
    }
}

struct Node
{
    std::variant<std::optional<double>, std::shared_ptr<Node>> x{ std::nullopt };
    std::variant<std::optional<double>, std::shared_ptr<Node>> y{ std::nullopt };

    double sign{ 1 };
    Type type{ Type::None };
};

#endif //UNTITLED1_TYPES_HPP
