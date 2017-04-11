/*----------------------------------------------------------------------
 Find Median from Data Stream

 Median is the middle value in an ordered integer list. If the size of the
 list is even, there is no middle value. So the median is the mean of the
 two middle value.

 Design a data structure that supports the following two operations:

 [1] void addNum(int num) - Add a integer number from the data stream to
                            the data structure.
 [2] double findMedian() - Return the median of all elements so far.

 Idea : Here we will be using two Heap to maintain left and right elements.
        The max element from leftHeap will always be equal or less compare to
        min element in rightHeap.

        With every number we add, we first check where this number should go,
        And then we check if we need to balance the heaps or not.

        For example, below is list of elements. Lets see how we manage heaps
        with every insert.

        Element         LeftHeap          rightHeap          Median
        -------------------------------------------------------------
        1               1                 empty              1
        3               1                 3                  2
        2               1                 2,3                2
        5               1,2               3,5                2.5
        4               1,2               3,4,5              3

 reference : Leetcode.com Problem # 295
----------------------------------------------------------------------*/
#include <iostream>
#include <queue>
#include <functional>
#include <vector>

using std::cout;
using std::greater;
using std::vector;
using std::priority_queue;


class MedianFinder
{
private:
   /* leftHeap is a max Heap, which means it offers O(1) look up time for max element
    * rightHeap is a min Heap, offering O(1) look up for min element
    */
   priority_queue<int> leftHeap;
   priority_queue<int, vector<int>, greater<int>> rightHeap;

public:
   MedianFinder()
   { }

   /* this is the function where we balance both heaps, by adding number and
    * shuffling them across heaps if required.
    */
   void addNum( int num )
   {
      /* we want to add this number in one of the queue. Very first number
       * would always go into leftHeap.
       */
      if( leftHeap.empty() )
      {
         leftHeap.push( num );
         return;
      }

      /* If leftHeap is not empty then compare the element with maximum element
       * from leftHeap.
       */
      if( num <= leftHeap.top())
      {
         /* num will go in leftHeap.
          */
         leftHeap.push( num );

         /* Check if we need to remove any element from leftHeap. This is to balance
          * out both heaps. At any time the size difference between two
          * heaps should only be 1.
          */
         if( leftHeap.size() > (1 + rightHeap.size()))
         {
            rightHeap.push( leftHeap.top() );
            leftHeap.pop();
         }

      }
      else
      {
         // num will go in rightHeap
         rightHeap.push( num );

         if( rightHeap.size() > (1 + leftHeap.size()) )
         {
            leftHeap.push( rightHeap.top() );
            rightHeap.pop();
         }
      }
   }

   double findMedian()
   {
      /* Median will be the middle element between left-right Heaps. Pick element from
       * the bigger size heap. If both heap has same size() then we consider average.
       */

      if( leftHeap.size() > rightHeap.size() )
      {
         return leftHeap.top();
      }
      else if( rightHeap.size() > leftHeap.size() )
      {
         return rightHeap.top();
      }
      else
      {
         return ( leftHeap.top() + rightHeap.top())/2.0 ;
      }
   }
};

int main()
{
   MedianFinder medFin;
   medFin.addNum(1);
   cout << "Median so far is : " << medFin.findMedian() << std::endl;
   medFin.addNum(3);
   cout << "Median so far is : " << medFin.findMedian() << std::endl;
   medFin.addNum(2);
   cout << "Median so far is : " << medFin.findMedian() << std::endl;
   medFin.addNum(6);
   medFin.addNum(4);
   medFin.addNum(5);
   cout << "Median so far is : " << medFin.findMedian() << std::endl;

   return 0;
}
