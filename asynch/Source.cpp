#include <iostream>
#include <future>

using namespace std;

int main()
{
	std::async(/*Launch Policy*/std::launch::async,
				/*Callable Object*/[]{
										cout<<"Hello World from Worker" << endl;
									});

	std::this_thread::sleep_for(std::chrono::seconds(3));

	cout << "Hello Form Main Thread" << endl;


	cin.get();
}
