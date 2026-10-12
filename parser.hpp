//
// Created by allosker on 11/10/2026.
//

#ifndef UNTITLED1_PARSER_HPP
#define UNTITLED1_PARSER_HPP

#include "str_convertions.hpp"
#include "types.hpp"
#include <string>


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


inline Node parse(std::string format) noexcept
{
  if (format.empty()) return {};

  Node ret;
  auto* ins = &ret;
  auto t = Type::None; // represents current operation type
  bool first_iter{ true };

  for (auto i = format.begin();;)
  {

      if (i != format.end() && *i == ')')
      {
          i = format.erase(i);

          if (i == format.end())
              break;

          continue;
      }

    bool erase_next_character{ true };

    if (first_iter)
        erase_next_character = false; // on the first iteration, the first sign (if negative) does not define an operation
    else
        t = char_to_type(*i);

        

    // Decide which operation affects the node
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
                Node temp{};

                temp.x = std::move(ins->y);
                ins->y = std::make_shared<Node>(std::move(temp));

                ins = std::get<std::shared_ptr<Node>>(ins->y).get();
            }
            else
                // Add a new node to the right
            {
                auto temp = std::move(ret);
                ret = {};

                ins = &ret;

                ins->x = std::make_shared<Node>(std::move(temp));
            }
        }

        ins->type = t;
        t = Type::None; // Reset t

        if (erase_next_character)
            i = format.erase(i);
    }

    // Evaluate sub-expressions
    if (i != format.end() && *i == '(')
    {
        std::string parenthesis{};
        get_inner_expression(parenthesis, format, i);

        auto op = std::get_if<std::optional<double>>(&ins->x);
        auto ptr = std::get_if<std::shared_ptr<Node>>(&ins->x);

        if (op || ptr)
        {
            if (op && !*op)
                ins->x = std::make_shared<Node>(std::move(parse(parenthesis)));
            else
                ins->y = std::make_shared<Node>(std::move(parse(parenthesis)));
        }
        else
        {
            ins->x = std::make_shared<Node>(std::move(parse(parenthesis)));
        }
    }

    // Get string of numbers (represents a scalar)
    std::string str_nb{};
    while (i != format.end())
    {
        auto temp = char_to_type(*i);
        
        if ((temp == Type::None || temp == Type::Subtract) && (*i != '(' && *i != ')'))
        {

            if (str_nb.empty() && *i == '-')
            {
                str_nb += *i;
                i = format.erase(i);

                while (i != format.end() || char_to_type(*i) == Type::None)
                {
                    if (char_to_type(*i) == Type::None && *i != '(' && *i != ')')
                    {
                        str_nb += *i;
                        i = format.erase(i);
                    }
                    else
                        break;
                }
                break;
            }
            else if (temp != Type::None)
                break;

            str_nb += *i;
        }
        else
        {
            break;
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
            *y = nb;
        }
    }


    first_iter = false;
    if (i == format.end()) break;
  }

    return ret;
}


#endif //UNTITLED1_PARSER_HPP
