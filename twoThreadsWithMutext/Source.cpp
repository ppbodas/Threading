#include <iostream>
#include <future>

using namespace std;

int mValue = 0;
std::mutex m;

void addValue()
{
	for (int i=0; i < 100000; ++i)
	{
		std::lock_guard<std::mutex> lg(m);
		//m.lock();
		++mValue;
		//m.unlock();
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
