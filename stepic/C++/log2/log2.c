#include <iostream>

using namespace std;

int log2(int x)
{
    int k = 0;
    while (x != 1)
    {
        x = x >> 1;
		cout << x << endl;
        k++;
    }
    return k;
}

int main()
{
    int nNumbers;
    cin >> nNumbers;
    for(int i = 0; i < nNumbers; i++)
    {
        int x;
        cin >> x; 
        cout << log2(x) << endl;
    }
    
    return 0;   
}
