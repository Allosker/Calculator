
#include <print>

#include "str_convertions.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "preprocessor.hpp"

double compute_value(const std::string& input) noexcept
{

	std::println("Original: {}", input);
	const auto& formatted_string = preprocess(input);
	std::println("Formatted: {}", formatted_string);

	const auto& tree = parse(formatted_string);
	double result = interpret(tree);

	return result;
}


int main()
{

	std::println("Result: {}", compute_value("(2.5)^2"));
	//std::println("Smth: {}", compute_value("(-4)^2-(-4^2)"));
	//std::println("Smth: {}", compute_value("(-2)^3^2")); // change that, it crashes, and also, normally -2 shouldn't be considered an unary minus
}