//
// Created by allosker on 10/10/2026.
//

#ifndef UNTITLED1_STR_CONVERTIONS_HPP
#define UNTITLED1_STR_CONVERTIONS_HPP

inline int pow10(int x, size_t n) noexcept
{
    if (n == 0) return x;

    int ret{ x };
    while (n > 0)
    {
        ret *= 10;
        --n;
    }
    return ret;
}

inline int char_to_nbr(char c) noexcept
{
    switch (c)
    {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
    }
}

inline int str_to_nbr(const std::string& str) noexcept
{
    int nb{};
    int nb_iterations{};
    for (auto i{ static_cast<int>(str.size()) }; i >= 0; i--)
    {
        const auto c = str[i];
        if (c == '\0') continue;

        nb += pow10(char_to_nbr(c), nb_iterations);
        nb_iterations++;
    }

    return nb;
}

inline bool is_scalar(char x)
{
    return x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9';
}

#endif //UNTITLED1_STR_CONVERTIONS_HPP
