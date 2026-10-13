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

inline double pow_minus_10(double x, long long n) noexcept
{
    double ret{ x };
    do
    {
        ret *= 0.1;
        --n;
    } while (n > 0);
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

inline long long str_to_int(const std::string& str, long long start, long long end) noexcept
{
    long long nb{};
    long long nb_iterations{};

    do
    {
        const auto c = str[end];

        nb += pow10(char_to_nbr(c), nb_iterations);
        nb_iterations++;
        
        end--;
    } 
    while (end >= start);

    return nb;
}

inline double str_to_decimal(const std::string& str, size_t start, size_t end) noexcept
{
    double nb{ static_cast<double>(str_to_int(str, start, end)) };

    return pow_minus_10(nb, end - start + 1);
}

inline double str_to_nbr(const std::string& str) noexcept
{
    bool negate{};

    size_t start{};
    size_t end{ str.size() - 1 };

    if (str[0] == '-')
    {
        negate = true;
        start++;
    }

    for (auto i = start; i != end; i++)
    {
        if (str[i] == '.')
        {
            end = i - 1; // add -1 to end to avoid '.' character
            break;
        }
    }


    double ret{ static_cast<double>(str_to_int(str, start, end)) };

    if (end < str.size() - 1)
        ret += str_to_decimal(str, end + 2, str.size() - 1); // add 2 to end to avoid '.' character

    
    return negate ? -ret : ret;
}

inline bool is_scalar(char x)
{
    return x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9' || x == '.';
}

#endif //UNTITLED1_STR_CONVERTIONS_HPP
