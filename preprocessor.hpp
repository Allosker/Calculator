//
// Created by allosker on 11/10/2026.
//

#ifndef UNTITLED1_PREPROCESSOR_HPP
#define UNTITLED1_PREPROCESSOR_HPP

#include "str_convertions.hpp"
#include "types.hpp"
#include <string>

std::string process(std::string raw_input) noexcept
{
	std::string format{};

	for (size_t i{}; i < raw_input.size(); i++)
	{
		const auto& previous = raw_input[i == 0 ? i : i - 1];
		const auto& current = raw_input[i];
		//const auto& next = raw_input[i + 1];

		if (current != ' ')
		{
			if (i != 0 && previous == '-' && current == '-') // you know what to do, recursive, scalar thingie
			{
				format += '(';
				format += current;
				format += '(';

				auto temp_cur = i + 1;
				while (char_to_type(current) == Type::Exponentiate || char_to_type(current) == Type::None)
				{
					if (temp_cur >= raw_input.size()) break;
					temp_cur++;
				}
				raw_input.insert(raw_input.begin() + temp_cur, ')');
				raw_input.insert(raw_input.begin() + temp_cur + 1, ')');

				continue;
			}

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
