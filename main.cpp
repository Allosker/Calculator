
#include <print>

#include "str_convertions.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "preprocessor.hpp"

double compute_value(const std::string& input) noexcept
{

  const auto& formatted_string = process(input);
  std::println("{}", formatted_string);

  const auto& tree = parse(formatted_string);
  double result = interpret(tree);

  return result;
}


int main()
{


  //std::println("Smth: {}", compute_value("(10 + 2) - 2"));
  std::println("Smth: {}", compute_value("10 + (-2) ^ 3 ^ 2"));
  //std::println("Smth: {}", compute_value("20 / 2 * 4"));
}