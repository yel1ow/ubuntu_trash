#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	for(int i : a)
	cout << i << " ";
	cout << endl;
	for(int i : a)
	if(i == 1)
	{
		i = 2;
		cout << "yes" << endl;
	}
	for(int i : a)
	cout << i << " ";
	cout << endl;
	return 0;
}
