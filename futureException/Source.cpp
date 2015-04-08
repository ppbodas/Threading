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

bool onlyOddAllowed (int num)
{
	if (num & 0x01)
		return true;
	
	throw SomeException();
}

int main()
{

	std::srand(unsigned(time(0)));

	int num = rand();
	std::future<bool>  fut = std::async(std::launch::async,[=]{return onlyOddAllowed(num);});


	try
	{
		if (fut.get())
			cout << num << " is Odd" << endl; 
	}
	catch(exception & e)
	{
		cout <<e.what() << endl;
	}


	//cin.get();
}
