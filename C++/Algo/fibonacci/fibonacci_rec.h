#pragma once

namespace my_algo
{
    int fibonacci_rec(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        else
        {
            return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
        }
    }

    int fibonacci_iter(int n)
    {
        if(n == 0 || n == 1)
            return 1;
        int num[2] = {1, 1};
        for(int i = 2; i <= n; i++)
        {
            num[i % 2] += num [1 - (i % 2)];
        }
        return num[n % 2];
    }
}
