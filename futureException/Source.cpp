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

bool isOdd (int num)
{
	if (num & 0x0001)
		return true;
	
	throw MyException();
}

int main()
{

	std::srand(unsigned(time(NULL)));

	int num = rand();
	std::future<bool>  fut = std::async(std::launch::async,[=]{return isOdd(num);});

	try
	{
		cout << num << " is " << fut.get() << endl; 
	}
	catch(exception & e)
	{
		cout <<e.what() << endl;
	}



	cin.get();
}
