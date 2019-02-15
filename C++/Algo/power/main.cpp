#include <iostream>
#include <chrono>
#include "power.h"

using std::cout;
using std::endl;

int main()
{
    auto begin = std::chrono::steady_clock::now();
    //begin
    for(int i = 0; i < 1000; i++)
    {
        cout << my_algo::slow_power(2.3, 10) << endl;
    }
    cout << my_algo::slow_power(2.3, 10) << endl;
    //end
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << ms.count()/1000.0 << " s\n";
    return 0;
}