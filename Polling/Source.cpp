#include <iostream>
#include <future>
#include <exception>

using namespace std;


int compute()
{
	std::this_thread::sleep_for(std::chrono::seconds(20));
	return 555;
}

int main()
{

	std::srand(unsigned(time(NULL)));

	int num = rand();
	std::future<int> fut = std::async(std::launch::async,[]{return compute();});

	while(std::future_status::ready != fut.wait_for(std::chrono::seconds(0)))
	{
		cout << "Wait for some time" << endl;
		this_thread::sleep_for(std::chrono::seconds(2));
	}

	cout << fut.get() << endl;



	cin.get();
}
