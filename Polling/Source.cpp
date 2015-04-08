#include <iostream>
#include <future>
#include <exception>

using namespace std;


int compute()
{
	std::this_thread::sleep_for(std::chrono::seconds(15));
	return 555;
}

int main()
{

	std::srand(unsigned(time(0)));

	int num = rand();
	std::future<int> fut = std::async(std::launch::async,[]{return compute();});

	//Lets wait till async call finishes
	while(std::future_status::ready != fut.wait_for(std::chrono::seconds(0)))
	{
		cout << "Inside main thread: Wait for worker to finish" << endl;
		this_thread::sleep_for(std::chrono::seconds(2));

		//May be do some other work here...
	}

	cout << fut.get() << endl;
	//cin.get();
}
