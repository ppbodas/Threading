#include <iostream>
#include <future>
#include <exception>

using namespace std;
class MyException : public exception
{
	const char * what () const throw ()
	{
		return "Exception";
	}

};

void onlyOdd (int num, std::promise<bool>& p)
{
	if (num & 0x0001)
	{
		p.set_value(true);
		return;
	}

	p.set_exception(std::make_exception_ptr(MyException()));

}

int main()
{
	srand(time(0));
	int num = rand();

	std::promise<bool> p;
	std::thread th(onlyOdd, num, std::ref(p));


	std::future<bool> fut = p.get_future();

	th.join();
	try
	{
		cout << num << " is odd " << fut.get() << endl;
	}
	catch(std::exception & e)
	{
		cout << num << endl << "Exception Thrown " << endl;
	}


	cin.get();
}
