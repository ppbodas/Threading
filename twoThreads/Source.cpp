#include <iostream>
#include <future>

using namespace std;

int mValue = 0;

void addValue()
{
	for (int i=0; i < 1000000; ++i)
	{
		++mValue;
	}
}

int main()
{

	future<void> fut1 = async(std::launch::async, addValue);
	future<void> fut2 = async(std::launch::async, addValue);

	fut1.get();
	fut2.get();

	cout << mValue << endl;
 


	//cin.get();
}
