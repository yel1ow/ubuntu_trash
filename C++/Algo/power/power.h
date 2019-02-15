#pragma once

namespace my_algo
{
    template <class T>
    T slow_power(T x, int n)
    {
        T result = 1;
        for(int i = 0; i < n; i++)
        {
            result *= x;
        }
        return result;
    }

    template <class T>
    int power(T x, int n)
    {
        int result = 1;
        int current_degree = x;
        while (n != 0)
        {
            if (n % 2 == 1)
            {
                result *= current_degree;
            }
            current_degree *= 2;
            n >> 1;
        }
        return result;
    }
}
