//
// Created by allosker on 11/10/2026.
//

#ifndef UNTITLED1_PREPROCESSOR_HPP
#define UNTITLED1_PREPROCESSOR_HPP

#include "str_convertions.hpp"
#include "types.hpp"
#include <string>

/// <summary>
/// Takes in the start of a string (a number sequence within that string), and returns the end of the sequence
/// <para> Note: this function assumes "start" is the first character in the sequence</para>
/// </summary>
/// <param name="start of sequence"></param>
/// <param name="end of string"></param>
/// <returns>One past the end of the sequence</returns>
std::string::const_iterator get_end_sequence(const std::string::const_iterator& start, const std::string::const_iterator& end) noexcept
{
	std::string::const_iterator end_sequence = start;
	while (end_sequence != end)
	{
		if (!is_scalar(*end_sequence)) return end_sequence;
		end_sequence++;
	}

	return end_sequence;
}

void emplace_parentheses(std::string& str)
{
	for (size_t i{}; i < str.size(); i++)
	{
		const auto& previous = str[i == 0 ? i : i - 1];
		const auto& current = str[i];

		if (i != 0 && previous == '-' && is_scalar(current))
		{
			str.insert(str.begin() + i, '(');
			i++;

			std::string::const_iterator es{};
			for (;;)
			{
				es = get_end_sequence(str.begin() + i, str.end());

				if (es != str.end() && char_to_type(*es) == Type::Exponentiate)
					i++;
				else
					break;	
			}
			str.insert(es, ')');
			i++;
		}
	}
}

std::string preprocess(std::string raw_input) noexcept
{
	std::string format{};

	emplace_parentheses(raw_input);

	for (size_t i{}; i < raw_input.size(); i++)
	{
		const auto& previous = raw_input[i == 0 ? i : i - 1];
		const auto& current = raw_input[i];

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
