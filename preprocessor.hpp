//
// Created by allosker on 11/10/2026.
//

#ifndef UNTITLED1_PREPROCESSOR_HPP
#define UNTITLED1_PREPROCESSOR_HPP

#include <string>
#include "str_convertions.hpp"

std::string process(const std::string& raw_input) noexcept
{
    std::string format{};

    for (size_t i{}; i < raw_input.size(); i++)
    {
        const auto& previous = raw_input[ i == 0 ? i : i - 1];
        const auto& current = raw_input[i];
        //const auto& next = raw_input[i + 1];

        if (current != ' ')
        {
            if ((is_scalar(previous) && current == '(') || (previous == ')' && is_scalar(current)) || (previous == ')' && current == '('))
            {
                format += '*';
                format += current;
                continue;
            }

            format += current;
        }
    }

    return format;
}

#endif //UNTITLED1_PREPROCESSOR_HPP
