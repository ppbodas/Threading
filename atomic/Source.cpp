#include <iostream>
#include <future>
#include <atomic>

using namespace std;

std::atomic<int> mValue = 0;
int mNonAtomic = 0;

void addValue()
{
	for (int i=0; i < 10000000; ++i)
	{
		++mValue;
		++mNonAtomic;
	}
}

int main()
{

	future<void> fut1 = async(std::launch::async, addValue);
	future<void> fut2 = async(std::launch::async, addValue);

	fut1.get();
	fut2.get();

	cout << mValue << endl;
	cout << mNonAtomic << endl;
 
	//cin.get();
}
