#include <iostream>
#include <future>
#include <atomic>
#include <mutex>
#include <stack>
#include <sstream>

using namespace std;

mutex coutMutex;

void print(stringstream& stream)
{
	lock_guard<mutex> lg(coutMutex);
	cout << stream.str();
}

bool _downloadFile(int num, int t)
{
	stringstream stream1;
	stream1 << "Download time for file " << num << " is: " << t << "seconds " << endl;
	print(stream1);
	this_thread::yield();
	this_thread::sleep_for(std::chrono::seconds(t));
	stringstream stream2;
	stream2 << "Download for file " << num << " is: " << "complete." << endl;
	print(stream2);

	return true;
}


class FileDownloader
{
public:
	FileDownloader(int num):mFileCount(num), mMinThreads(5), mIndex(0){}

	bool downloadAll()
	{
		vector<future<bool> > futures;

		for (int i = 0; i < mMinThreads; ++i)
		{
			futures.push_back(async(launch::async, [this]{ return downloadFile();}));
			this_thread::sleep_for(std::chrono::seconds(1));
		}

		for (future<bool>& f : futures)
		{
			f.get();
		}
		return true;
	}
private:
	bool downloadFile()
	{
		std::srand(unsigned(time(0)));

		int index = mIndex++;
		
		while (index < mFileCount)
		{
			int t = rand() % 5 + 2;
			_downloadFile(index, t);

			index = mIndex++;

			stringstream stream1;
			stream1 << "Next file to download: " << index << endl;
			print(stream1);
		}
		return true;
	}
	
private:
	const int mFileCount;
	const int mMinThreads;
	atomic<int> mIndex;
	
};

int main()
{
	std::srand(unsigned(time(NULL)));

	int fileCount = 25; //rand() % 5 + 5;

	cout << "Total Files to download: " << fileCount << endl;
	FileDownloader downloader(fileCount);

	downloader.downloadAll();	

	cout << "Completed all downloads" << endl;
	cin.get();
}