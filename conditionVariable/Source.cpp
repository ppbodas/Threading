#include <iostream>
#include <future>
#include <mutex>

using namespace std;

int a = 0;
int b = 5;
mutex m;
bool bReadyState = false;
std::condition_variable conditionVar;

bool producer()
{
	cout << "Inside Producer Thread" << endl;
	std::this_thread::sleep_for(std::chrono::seconds(15));
	a = 3;
	std::lock_guard<std::mutex>lg (m);
	bReadyState = true;
	conditionVar.notify_one();
	return true;
}

bool consumer()
{
	cout << "Inside Consumer Thread" << endl;
	{
		std::unique_lock<std::mutex>ul (m);
		conditionVar.wait(ul, []{return bReadyState;});
	}
	cout << "Multiplication is " << a * b << endl;
	return true;
}
int main()
{
	std::future<bool>  fut1 = std::async(std::launch::async,producer);
	std::future<bool>  fut2 = std::async(std::launch::async,consumer);

	fut2.get();
	//cin.get();
}
