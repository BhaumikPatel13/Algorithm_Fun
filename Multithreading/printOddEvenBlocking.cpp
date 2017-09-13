/*
	Print Odd-Even numbers using multi-threading.
	Numbers must be printed in correct order.

	This solution is using wait-notify mechanism. Here we are
	using condition variable to achieve wait-notify. This is
	better than busy waiting since threads will be blocked here,
	until notified.

	"PrintOdd" is waiting for " Odd number condition ", so it will
	be blocked if number is even. And opposite for printEven thread.
	After increasing n (n++), both threads will notify each other.

	We are using unique_lock, since cond.wait needs to unlock it if
	condition isn't met.

*/
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

using std::mutex;
using std::cout;
using std::unique_lock;
using std::endl;
using std::condition_variable;


class OddEven
{
	mutex mt;
	condition_variable cond;
	int n;

public:
	OddEven():n(1)
	{}

	void printOdd(int target)
	{
		while( n < target )
		{
			unique_lock<mutex> lck(mt);
			cond.wait(lck, [=](){ return n%2==1;} );
			cout << n++ << endl;
			lck.unlock();
			cond.notify_one();
		}
	}

	void printEven(int target)
	{
		while( n < target )
		{
			unique_lock<mutex> lck(mt);
			cond.wait(lck, [=](){ return n%2==0;} );
			cout << n++ << endl;
			lck.unlock();
			cond.notify_one();
		}
	}

};

int main()
{
	OddEven x;
	int target = 20;
	std::thread t1( &OddEven::printOdd, &x, target);
	std::thread t2( &OddEven::printEven, &x, target);

	t1.join();
	t2.join();

   return 0;
}
