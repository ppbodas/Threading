#include <iostream>
#include <thread>

using namespace std;

int main()
{
	std::thread th(/*Callable Object*/[]
				{
					cout<<"Hello World From Worker Thread" << endl;
				});

	std::this_thread::sleep_for(std::chrono::seconds(3));

	cout << "Hello Form Main Thread" << endl;

	th.join();
	//cin.get();
}
