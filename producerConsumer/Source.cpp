#include <iostream>
#include <future>
#include <mutex>

using namespace std;

int a = 0;
int b = 5;
mutex m;
bool bReadyState = false;

bool producer()
{
	cout << "Inside Producer Thread" << endl;
	std::this_thread::sleep_for(std::chrono::seconds(15));
	a = 3;
	std::lock_guard<std::mutex>lg (m);
	bReadyState = true;
	return true;
}

bool consumer()
{
	{
		std::unique_lock<std::mutex>ul (m);
		int pollCount = 0;
		while (false == bReadyState)
		{
			ul.unlock();
			cout << "Inside Consumer Thread: " << ++pollCount << endl;
			this_thread::yield;
			this_thread::sleep_for(std::chrono::seconds(2));
			ul.lock();
		}
	}
	cout << "Multiplication is " << a * b << endl;
	return true;
}
int main()
{
	std::future<bool>  fut1 = std::async(std::launch::async,producer);
	std::future<bool>  fut2 = std::async(std::launch::async,consumer);

	fut1.get();
	fut2.get();
	cin.get();
}
