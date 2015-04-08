#include <iostream>
#include <future>

using namespace std;

bool isOdd (int num)
{
	if (num & 0x1)
		return true;

	return false;
}

int main()
{

	std::srand(unsigned(time(0)));

	int num = rand();
	std::future<bool>  fut = std::async(std::launch::async, isOdd, num);

	if (fut.get())
	{
		cout << num << " is Odd Number" << endl; 
	}
	else
	{
		cout << num << " is Even Number" << endl; 
	}


	//cin.get();
}
