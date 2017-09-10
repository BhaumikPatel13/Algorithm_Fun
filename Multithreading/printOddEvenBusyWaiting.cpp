/*
	Print Odd-Even numbers using multi-threading.
	Numbers must be printed in correct order.

	Here is the basic solution using a single mutex.
	Since single mutex is used, threads will spend too much
	time busy waiting.

	Single mutex will protect  access to "n", "turn" and "cout".
	"turn" is needed to ensure the ordering. Odd thread will print
	when turn = 1 and even thread will print when turn = 2.

*/
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

using std::mutex;
using std::cout;
using std::lock_guard;
using std::endl;

class OddEven
{
	mutex mt;
	int n;
	int turn;

public:
	OddEven():n(1), turn(1)
	{}

	void printOdd(int target)
	{
		while( n < target)
		{
			lock_guard<mutex> lck(mt);
			if( turn == 1 )
			{

				cout << n++ << endl;
				turn = 2;
			}
		}
	}

	void printEven(int target)
	{
		while( n < target)
		{
			lock_guard<mutex> lck(mt);
			if( turn == 2 )
			{
				cout << n++ << endl;
				turn = 1;
			}
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
