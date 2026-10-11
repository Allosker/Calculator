//
// Created by allosker on 11/10/2026.
//

#ifndef UNTITLED1_PARSER_HPP
#define UNTITLED1_PARSER_HPP

#include <string>
#include "types.hpp"
#include "str_convertions.hpp"

inline void get_inner_expression(std::string& out, std::string& format, auto& i) noexcept
{
  i = format.erase(i); // get past first parenthesis
  while (i != format.end() && *i != ')')
  {

    if (*i == '(')
    {
      out += *i;
      get_inner_expression(out, format, i);
    }
    out += *i;

    if (*i != ')')
      i = format.erase(i);
  }

  out += *i; // If it stops when i == ')', it means it will be this character
  i = format.erase(i);
};


inline Instruction parse(std::string format) noexcept
{
  if (format.empty()) return {};

  Instruction ret;
  auto* ins = &ret;
  auto t = Type::None; // represents current operation type
  double sign{ 1 };

  for (auto i = format.begin();;)
  {
    t = char_to_type(*i);
    // Decide which operation affect the instruction
    if (t != Type::None)
    {

      if (ins->type != Type::None)
      {
        if ((t == Type::Exponentiate && (ins->type == Type::Add || ins->type == Type::Subtract || ins->type == Type::Multiply || ins->type == Type::Divide))
        || (t == Type::Exponentiate && ins->type == Type::Exponentiate)
        || ((t == Type::Multiply || t == Type::Divide) && (ins->type == Type::Add || ins->type == Type::Subtract))
        || (t == Type::Multiply && ins->type == Type::Multiply))
          // Right-to-Left precedence
        {
          Instruction temp{};

          temp.x = std::move(ins->y);
          ins->y = std::make_shared<Instruction>(std::move(temp));

          ins = std::get<std::shared_ptr<Instruction>>(ins->y).get();
        }
        else
          // Add a new instruction to the right
        {
          auto temp = std::move(ret);
          ret = {};

          ins = &ret;

          ins->x = std::make_shared<Instruction>(std::move(temp));
        }
      }

      ins->type = t;
    }



    // Get string of numbers (represents a scalar)
    std::string str_nb{};
    auto temp = Type::None;
    while (i != format.end())
    {
      if (*i != '(' && *i != ')')
      {
        if (temp == Type::None)
          temp = char_to_type(*i);

        if (temp != Type::None)
        // Consume the operator -> for +/- this works as a sign
        {
          if (*i == '-')
          {
            sign = -1;
            t = Type::Subtract;
          }

          if (!str_nb.empty())
          {
            if (temp != t) t = temp;

            break;
          }
          i = format.erase(i);
        }

        // Evaluate sub-expressions
        if (*i == '(')
        {
          std::string parenthesis{};
          get_inner_expression(parenthesis, format, i);

          auto op = std::get_if<std::optional<double>>(&ins->x);
          auto ptr = std::get_if<std::shared_ptr<Instruction>>(&ins->x);

          if (op || ptr)
          {
            if (op && !*op)
              ins->x = std::make_shared<Instruction>(std::move(parse(parenthesis)));
            else
              ins->y = std::make_shared<Instruction>(std::move(parse(parenthesis)));
          }
          else
          {
            ins->x = std::make_shared<Instruction>(std::move(parse(parenthesis)));
          }
        }


        str_nb += *i;
      }

      i = format.erase(i);
    }

    // Add a number to the right or left
    std::optional<double> nb = std::nullopt;
    if (!str_nb.empty())
    {
      nb = std::make_optional(str_to_nbr(str_nb));

      auto x = std::get_if<std::optional<double>>(&ins->x);
      auto y = std::get_if<std::optional<double>>(&ins->y);

      if (x && !*x)
      {
        *x = nb;
      }
      else if (y && !*y)
      {
        if (std::get_if<std::shared_ptr<Instruction>>(&ins->x))
        {
          if (t == Type::Subtract)
          {
            auto nbr = *nb;
            *y = std::make_optional(nbr * sign);
            sign = 1;
            ins->type = Type::Add;
          }
          else
            *y = nb;
        }
        else
          *y = nb;
      }
    }



    if (i == format.end()) break;
  }

  return ret;
}


#endif //UNTITLED1_PARSER_HPP
