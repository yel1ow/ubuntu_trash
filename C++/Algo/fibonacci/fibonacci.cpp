#include <iostream>
#include <chrono>
#include "fibonacci_rec.h"
#include "fibonacci_iter.h"

int main()
{
    auto begin = std::chrono::steady_clock::now();
    //begin
    std::cout << my_algo::fibonacci_rec(30) << std::endl;
    std::cout << my_algo::fibonacci_iter(30) << std::endl;
    //end
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << ms.count()/1000.0 << " s\n";
    return 0;
}