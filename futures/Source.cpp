#include <iostream>
#include <future>

using namespace std;

bool isOdd (int num)
{
	if (num & 0x0001)
		return true;

	return false;
}

int main()
{

	std::srand(unsigned(time(NULL)));

	int num = rand();
	std::future<bool>  fut = std::async(std::launch::async,[=]{return isOdd(num);});

	if (fut.get())
	{
		cout << num << " is Odd" << endl; 
	}
	else
	{
		cout << num << " is Even" << endl; 
	}


	//cin.get();
}
