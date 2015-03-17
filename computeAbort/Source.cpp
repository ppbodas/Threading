#include <iostream>
#include <future>
#include <exception>
#include <time.h>

using namespace std;

bool bStopProcessing = false;

class ComputeTerminatedException : public exception
{
	const char * what()
	{
		return "Compute Terminated by User";
	}
};

bool stopProcessing()
{
	return bStopProcessing;
}

int fastCompute()
{
	return 111;
}

int fullCompute()
{
	srand(time(0));

	int value = rand();

	cout << value << endl;
	if(value & 0x0001)		//for odd numbers
	{
		for (int i = 0; i < 5; ++i)
		{
			//Do some work
			std::this_thread::sleep_for(std::chrono::seconds(3));
			if (stopProcessing())
			{
				throw ComputeTerminatedException();
			}
		}
		return 555;
	}
	else
	{
		this_thread::sleep_for(std::chrono::seconds(4));
		return 666;
	}
}

int main()
{

	std::srand(time(NULL));

	int num = rand();
	std::future<int> fut = std::async(std::launch::async,[]{return fullCompute();});

	this_thread::sleep_for(std::chrono::seconds(8));

	if(std::future_status::ready == fut.wait_for(std::chrono::seconds(0)))
	{
		cout << "Using value from full compute" << endl;
		cout << fut.get() << endl;
	}
	else
	{
		cout << "Full compute is taking lot of  time. Aborting  that!!!" << endl;
		bStopProcessing = true;
		cout << "Using value from fast compute" << endl;
		cout << fastCompute() << endl;
	}

	cin.get();
}
