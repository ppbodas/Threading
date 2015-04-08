#include <iostream>
#include <future>
#include <exception>

using namespace std;
class SomeException : public exception
{
	const char * what () const throw ()
	{
		return "Exception: Ah You Sent Even Nubmer";
	}
};

void onlyOdd (int num, std::promise<bool>& p)
{
	if (num & 0x01)
	{
		p.set_value(true);
		return;
	}
	p.set_exception(std::make_exception_ptr(SomeException()));

}

int main()
{
	srand(time(NULL));
	int num = rand();

	std::promise<bool> p;
	std::thread th(onlyOdd, num, std::ref(p));


	std::future<bool> fut = p.get_future();

	th.join();
	try
	{
		if (fut.get())
		{
			cout << num << " is odd " << endl;
		}
	}
	catch(std::exception & e)
	{
		cout << num << endl << e.what() << endl;
	}


	//cin.get();
}
