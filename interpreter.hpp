//
// Created by allosker on 11/10/2026.
//

#ifndef UNTITLED1_INTERPRETER_HPP
#define UNTITLED1_INTERPRETER_HPP

#include <cmath>
#include "types.hpp"

double interpret(const Instruction& ins) noexcept
{
    std::optional<double> val1{};
    std::optional<double> val2{};

    if (auto x = std::get_if<std::shared_ptr<Instruction>>(&ins.x))
    {
        val1 = interpret(*x->get());
    }
    else
    {
        if (auto val = std::get_if<std::optional<double>>(&ins.x))
            val1 = *val;
        else
            val1 = std::nullopt;
    }

    if (auto y = std::get_if<std::shared_ptr<Instruction>>(&ins.y))
    {
        val2 = interpret(*y->get());
    }
    else
    {
        if (auto val = std::get_if<std::optional<double>>(&ins.y))
            val2 = *val;
        else
            val2 = std::nullopt;
    }

    if (!val1) return *val2;
    else if (!val2) return *val1;

    switch (ins.type)
    {
        case Type::Add:
            return  *val1 + *val2;
        case Type::Subtract:
            return *val1 - *val2;
        case Type::Multiply:
            return *val1 * *val2;
        case Type::Divide:
            return *val1 / *val2;
        case Type::Exponentiate:
            return std::pow(*val1, *val2);
    }
}


#endif //UNTITLED1_INTERPRETER_HPP
