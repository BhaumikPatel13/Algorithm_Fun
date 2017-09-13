/*
 *  Implement a simple reader-writer ( producer-consumer) with a
 *  single reader and single writer.
 *
 *  Here we have implemented a basic thread safe Queue as "sharedQueue".
 *  Writer will write to queue and reader will read it from queue.
 *
 *  Synchronization is achieved within Queue itself by using a mutex and
 *  a condition variable.
 *
 *  We also have used a global mutex ("printMtx") to synchronize access
 *  to "cout", since both threads will be printing output to cout.
 */
#include<iostream>
#include<thread>
#include<deque>
#include<mutex>
#include<condition_variable>
#include<chrono>

using std::thread;
using std::deque;
using std::cout;
using std::endl;
using std::unique_lock;
using std::mutex;
using std::condition_variable;
using std::lock_guard;

mutex printMtx;

/*
 *  sharedQueue is a thread safe queue, shared between reader and writer.
 */
template< typename T >
class sharedQueue
{
  deque<T> _buffer;
  const size_t _size = 15;

  mutex _bufMtx;
  condition_variable _bufCond;

public:
  sharedQueue()
  {}

  void write(const T&);
  const T& read();
};

template<typename T>
void sharedQueue<T>::write(const T& value )
{
  unique_lock<mutex> lck(_bufMtx);
  _bufCond.wait(lck, [this](){ return _buffer.size() < _size ;} );
  _buffer.push_back(value);
  lck.unlock();
  _bufCond.notify_all();
  return;
}

template<typename T>
const T& sharedQueue<T>::read()
{
  unique_lock<mutex> lck(_bufMtx);
  _bufCond.wait(lck, [this](){ return _buffer.size() > 0; } );
  const T& readItem = _buffer.front();
  _buffer.pop_front();
  lck.unlock();
  _bufCond.notify_all();
  return readItem;
}

/*
 * Reader will read data from sahredQueue.
 * Read thread sleeps for 300 seconds, over time it will be
 * exactly 15 elements behind writer thread, since our queue
 * size is 15.
 */
class Reader
{
  sharedQueue<int> &q;
public:
  Reader( sharedQueue<int>& buffer ):q(buffer)
  {}

  void readData()
  {
    while(true)
    {
      std::this_thread::sleep_for( std::chrono::milliseconds(300) );
      int result = q.read();
      lock_guard<mutex> lck(printMtx);
      cout << "Read : " << result << endl;
    }
  }
};

/*
 * Writer will write data to sharedQueue.
 * Writer is faster due to less sleep time (200ms) compare
 * to reader.
 */
class Writer
{
  sharedQueue<int> &q;
public:
  Writer( sharedQueue<int>& buffer ):q(buffer)
  {}

  void writeData()
  {
    int i=0;
    while(true)
    {
      std::this_thread::sleep_for( std::chrono::milliseconds(200) );
      q.write(i);
      lock_guard<mutex> lck(printMtx);
      cout << "Wrote : " << i++ << endl;
    }
  }
};

int main()
{
  sharedQueue<int> sq;
  /*
   * Both reader and writer are sharing the same queue.
   */
  Reader r(sq);
  Writer w(sq);

  thread t1(&Writer::writeData, &w);
  thread t2(&Reader::readData, &r);

  t1.join();
  t2.join();

  return 0;
}
