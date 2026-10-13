
#include <print>

#include "str_convertions.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "preprocessor.hpp"

double compute_value(const std::string& input) noexcept
{

  const auto& formatted_string = preprocess(input);
  std::println("{}", formatted_string);

  const auto& tree = parse(formatted_string);
  double result = interpret(tree);

  return result;
}


int main()
{

	//std::println("smth: {}", preprocess("2-3^3^3"));
	//std::println("Smth: {}", compute_value("((8-3)*(-2+6))^2-3^3"));
	std::println("Smth: {}", compute_value("-2^3^2")); // change that, it crashes, and also, normally -2 shouldn't be considered an unary minus
}