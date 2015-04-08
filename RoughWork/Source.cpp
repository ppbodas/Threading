#include <iostream>
#include <future>
#include <exception>

using namespace std;

void foo()
{
	cout << "Start Worker:" << endl;
	this_thread::sleep_for(std::chrono::seconds(15));
	cout << "End Worker:" << endl;
}

int main()
{
	cout << "Inside main: " << endl;
	future<void> fut = async(std::launch::async, foo);

	this_thread::sleep_for(std::chrono::seconds(2));
	cout << "End of main: " << endl;
}