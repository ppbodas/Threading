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

	cout << num << " is " << fut.get() << endl; 


	//cin.get();
}
